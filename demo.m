function demo()

% load data
img = importdata('img.mat');
im = img.im; % color image
imd = img.imd; % depth image, pixel in meters

% initialize a plane
plane = initPlane(imd);

% perform Selection selection
[roi, ~] = roi_selection(imd, plane);

% show image
im_show = uint8(bsxfun(@times,double(im),roi));
imshow(im_show);
fprintf('Black regions correspond to ground pixels\n')
fprintf('Those ground pixels not identified are invalid\n')

% extract candidate boxes
imdfilled = fillHoles(imd,'avg',5);
boxes = getBoxes(imd,imdfilled,roi,0.3); % box = [x1 y1 x2 y2]


end
