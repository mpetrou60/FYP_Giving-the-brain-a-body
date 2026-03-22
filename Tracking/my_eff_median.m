function [median_out, hist_out, ltm] = my_eff_median(image, old_hist, old_median, mask_size, row, col, ltm)
% -----------------------------------------------------------------------
% Function that calculate the median of an image window with given size and
% position. This function is taken from Huang T's algorithm for fast
% two-dimensional median filtering for image processing tasks.
% 
% Input
% image: image to be filtered. This will be a matrix of arbitrary size
% old_hist: histogram of previous window
% old_median: median output of previous window
% mask_size: size of mask used for window. This should be an odd number 
%               such as 3, 5, etc. 
% row:  current row number of pixel to be mean filtered
% column: current column number of pixel to be mean filtered
% ltm: current number of pixels that are less than the median.
%
% Output
% median_out: calculated median of window around specified pixel in image
% hist_out: output histogram of window
% ltm: number of pixels less than the median in array of current window
% -----------------------------------------------------------------------

% data is the window around the current pixel with given mask size
data = image(row-floor(mask_size/2):row+floor(mask_size/2), col+floor(mask_size/2));

% reshape data so that it is a vector rather than a matrix
data = reshape(data', 1, []); 

% old_data is the window around the previous pixel with given mask size
old_data = image(row-floor(mask_size/2):row+floor(mask_size/2), col-floor(mask_size/2)-1);

% reshape old_data so that it is a vector rather than a matrix
old_data = reshape(old_data', 1, []);

% define threshold value and other parameters
th = floor((mask_size^2)/2);
n = length(data);
hist = old_hist;

% --- update histogram ---------------------------------------------------

% delete the leftmost column of the previous window 
for i=1:n
    % check if value is less than the median
    if old_data(i) < old_median

        % increment counter
        ltm = ltm - 1;
    end

    % Remove data from the number it represents in the histogram. Note histogram
    % will go from 1-256 but greyscale is 0-255 so add 1 to position.
    hist(old_data(i)+1) = hist(old_data(i)+1) - 1;
end

% add the rightmost column of the current window
for i=1:n
    % check if value is less than the median
    if data(i) < old_median

        % increment counter
        ltm = ltm + 1;
    end

    % Add data to the number it represents in the histogram.
    hist(data(i)+1) = hist(data(i)+1) + 1;
end

% copy variables
median_out = old_median;
hist_out = hist;

% --- find the median ---------------------------------------------------
% median of current window is smaller than the one in the previous window
if ltm > th
    % Repeat while the above statement is true
    while ltm > th

        % decrement median
        median_out = median_out - 1;

        % decrement counter based on value in histogram for new median
        ltm = ltm - hist(median_out+1);
    end
% median of current window is greater than the one in the previous window
else
    % Repeat while the above statement is true
    while ltm + hist(median_out+1) <= th

        % increment counter based on value in histogram for new median
        ltm = ltm + hist(median_out+1);

        % increment median
        median_out = median_out + 1;
    end
end

end
