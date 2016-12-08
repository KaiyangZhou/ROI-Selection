function [ box_lambda ] = getBoxes( imd, imdfilled, roi, thre_ratio )
% thre_ratio: if a box where the ratio of number of valid pixels is less
% than this value, the box is discarded. This is a free parameter

if ~exist('thre_ratio', 'var')
    thre_ratio = 0; % no filtering
end

if nnz(roi) > 0
    str = 5; % stride
    % depth is used to generate lambda
    % II is an integral image describing sum of valid pixels at a location
    % thre_ratio defines the threshold to discard boxes that contain mainly
    % invalid pixels, thre_ratio -> [0,1]
    imd(imd > 0) = 1; % convert into a binary map
    II = computeII_mex(imd);
    [boxes, lambda] = generate_box_mex(roi,str,imdfilled,II,thre_ratio);
    %box_lambda = horzcat(boxes, lambda);
    box_lambda = boxes; % noly output boxes
else
    box_lambda = [];
end


end

