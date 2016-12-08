function [ Xw, Yw ] = local2world( imd )
% Project points into world coordinate system
% input:
%   imd: depth image, without hole filling and with unit in meters
% output:
%   X: horizontal, Y: vertical, both are 2D maps
%
% Image coordinate system to world coordinate system:
%  x_world = (x_screen - c_x) * z_world / f_x
%  y_world = (y_screen - c_y) * z_world / f_y

% intrinsics of the depth camera
fx = 5.9421434211923247e+02;
fy = 5.9104053696870778e+02;
cx = 3.3930780975300314e+02;
cy = 2.4273913761751615e+02;

[m, n] = size(imd);
[y, x] = ndgrid(1:m, 1:n);
y = m - y + 1; % set origin to bottom left

% transformation
Xw = (x - cx) .* (imd / fx);
Yw = (y - cy) .* (imd / fy);

% plot 3d point
% plot3(Xw,imd,Yw,'b.')
% xlabel('X')
% ylabel('Y')
% zlabel('Z')





end

