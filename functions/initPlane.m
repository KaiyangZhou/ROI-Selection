function [ plane ] = initPlane( imd, mode )
% Initialise ground plane and ceiling
% mode: 'groundOnly'(default) or 'groundAndCeiling'
% Output:
%   newPlane: 4-by-1 vector, [a b c d]' 
%   where ax + by + cz + d = 0 defining a plane

if ~exist('mode','var')
    mode = 'groundOnly';
end

[Xw, Yw] = local2world(imd);

% Ground plane
XYZ = sampling(Xw,Yw,imd,'lowerHalf');
% filter out unreliable datapoints
XYZ = ptsFilter(XYZ);
plane.ground = ransac(XYZ,[]);

% Ceiling
if strcmp(mode, 'groundAndCeiling')
    XYZ = sampling(Xw,Yw,imd,'upperHalf');
    plane.ceiling = ransac(XYZ,[]);
else
    plane.ceiling = [];
end


end

