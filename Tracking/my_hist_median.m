function [median_out, hist_out, ltm] = my_hist_median(image, mask_size, row, col)
% -----------------------------------------------------------------------
% Function that calculate the median of an image window with given size and
% position. This function can be applied to both the Median Filter and the 
% Efficient Median Filter for image processing tasks.
% 
% Input
% image: image to be filtered. This will be a matrix of arbitrary size
% mask_size: size of mask used for window. This should be an odd number 
%               such as 3, 5, etc. 
% row:  current row number of pixel to be mean filtered
% column: current column number of pixel to be mean filtered
%
% Output
% median_out: calculated median of window around specified pixel in image
% hist_out: output histogram of window
% ltm: number of pixels less than the median in array of current window
% -----------------------------------------------------------------------

% data is the window around the current pixel with given mask size
data = image(row-floor(mask_size/2):row+floor(mask_size/2), col-floor(mask_size/2):col+floor(mask_size/2));

% reshape data so that it is a vector rather than a matrix
data = reshape(data', 1, []); 
n = length(data);
hist = zeros(1,256);

% Iterate through the flattened window
for i=1:n
    % Add data to the number it represents in the histogram. Note histogram
    % will go from 1-256 but greyscale is 0-255 so add 1 to position.
    hist(data(i)+1) = hist(data(i)+1) + 1; 
end

% copy variable
hist_out = hist;
k = 1;

% Iterate through the histogram
for j=1:256
    % Check when there a pixel has been added to the histogram
    while hist(j)>0
        % set current pixel to the number in the histogram
        sorted_data(k) = j-1;

        % decrement histogram
        hist(j) = hist(j) - 1;

        % increment counter
        k = k + 1;
    end
end

% Median is the centre value of ordered array
median_out = sorted_data(ceil(length(sorted_data)/2));

% Calculate number of pixels less than median, this is not used for a
% normal histogram search but is used in the efficient version.
ltm = 0;
% iterate through flattened window
for i=1:n
    % check if value is less than the median
    if data(i) < median_out
        
        % increment counter
        ltm = ltm + 1;
    end
end

end