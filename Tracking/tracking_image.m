%-------------------------------------------------------------------------
% Project: FYP Giving the Brain a Body
% Authors: Maria N. Petrou
% Description: Noise reduction of Synthetic Aperture Radar (SAR) and
%               Ultraosund images using nonlinear filters.
% -------------------------------------------------------------------------
clear, clc, close all

%% --- Display image ----------------------------------------------------------------------------------------
% read image as a matrix 
Xo = imread('worm_pic.jpg');

% Reduce from rgb to greyscale image (3 dimensions to 2)
Xo = rgb2gray(Xo);

% downsample image to reduce computing time - repeat for both dimensions of
% matrix
Xo = downsample(Xo,5);
Xo = downsample(Xo.',5);


figure(3)
imshow(Xo)
title("Greyscale Unfiltered Image")
Xo = imadjust(Xo, [], [], 4); 
whos

% Display the origianl image and the edge detection output of original
% image

original_edge = edge(Xo, "sobel");

%% --- Efficient 2D Median Filter -----------------------------------------------------------------------------------
% Create a mask for the median filter and display using a histogram for 
% the sorting method. Results in an identical output as previous median
% filters but is much more computationally efficient.

% create a mask for the mean filter and display 
disp("Efficient 2D Median Filter")

% Define the number of rows and columns in image and the mask size to be
% used.
[n_rows, n_cols] = size(Xo);
mask_size = 9;

% Boundary replication by mirroring all pixels within the size of the mask
X = [Xo(1:mask_size,:); Xo; Xo(end-mask_size:end,:)]; 
X = [X(:,1:mask_size), X, X(:,end-mask_size:end)]; 

% Storage and initialisation of parameters
x_my_eff_median = zeros(n_rows, n_cols);
x_my_eff_median=uint8(x_my_eff_median);
m = 1;
n = 1;
ltm = 4;

% Iterates through each row and column in the image
for i = mask_size-1:1:n_rows+(mask_size-2)
    for j = mask_size-1:1:n_cols+(mask_size-2)
        % Calculates the median of the current window using the normal
        % histogram method until the mask size is exceeded
        if j <= mask_size
            [median_out, hist, ltm] = my_hist_median(X, mask_size, i, j);

        % Calculates the median of the current window using the efficient
        % method for all other points in the image
        else
            [median_out, hist, ltm] = my_eff_median(X, hist, median_out, mask_size, i, j, ltm);            
        end

        % Replace current pixel value with calculated median
        x_my_eff_median(m,n) = median_out;

        % keep a history of the previous median value
        old_median = median_out; 
        n = n + 1;
    end
    m = m + 1;
    n = 1;
end

% Display the output filtered image
% figure, imshow(x_my_eff_median)

% Display the detection output of filtered image
% figure, edge(x_my_eff_median, "sobel")

new_edge = edge(x_my_eff_median, "sobel");
superimpose = imfuse(new_edge, original_edge);
figure, imshow(superimpose)

figure(2)
subplot(2,2,1)
imshow(Xo)
title("Greyscale Unfiltered Image")
subplot(2,2,2)
edge(Xo, "sobel")
title("Sobel Edge Detection Unfiltered Image")
subplot(2,2,3)
imshow(x_my_eff_median)
title("Median Filtered Image")
subplot(2,2,4)
edge(x_my_eff_median, "sobel")
title("Sobel Edge Detection Filtered Image")

figure(3)
imshow(Xo)
title("Greyscale Unfiltered Image")
figure(4)
edge(Xo, "sobel")
title("Sobel Edge Detection Unfiltered Image")
figure(5)
imshow(x_my_eff_median)
title("Median Filtered Image")
figure(6)
edge(x_my_eff_median, "sobel")
title("Sobel Edge Detection Filtered Image")

% Enlarge figure to full screen.
% set(gcf, 'Units', 'Normalized', 'Outerposition', [0, 0.05, 1, 0.95]);

% opening function to fill any gaps
se = strel('rectangle',[20, 10]);
closeBW = imclose(new_edge,se);
figure, imshow(closeBW)

openBW = imopen(closeBW,se);
figure, imshow(openBW)

% skeletoniser to get spine