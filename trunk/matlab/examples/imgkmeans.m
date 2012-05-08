function [I] = imgkmeans(img, k, threshold, radius)
% Apply k-means to an EM image for segmentation.
% - k is the number of clusters to use
% - threshold. The image is scaled to have values between 0 and 1. After 
% applying k-means, the matrix of cluster values C is formed. Those 
% clusters with values lower than the threshold are set to 0
% - radius. After apply k-means and the threshold, the pixels of the 
% compressed image outside this radius are set to 0 too.


% img = load('image020.txt','ascii');
B = ( img - min(img(:))) / (max(img(:)) - min(img(:)));
imshow(B);
pause;
V = B(:);
ss = statset('MaxIter', 400);
[idx, C] = kmeans(V, k, 'options', ss);
% set 0 where C < threshold
C ( C < threshold) = 0; 
for i = 1:k;
    V( idx == i) = C(i);
end
I = reshape(V, size(B));

% clean pixels out of the circle
rows = size(I,1);
cols = size(I,2);
center = size(I)/2;
r = radius^2;
for i = 1:rows
    for j = 1:cols
        if((i-center(1))^2 + (j-center(2))^2 > r)
            I(i,j) = 0;
        end
    end
end
