function [ plane ] = updatePlane( Xw, Yw, imd, plane )

% update ground
XYZ = sampling(Xw,Yw,imd,'lowerHalf');
% collect datapoints that are close to the old plane to reduce search space
dis = calcDistance(plane.ground, 'XYZ', XYZ);
ind = dis < 0.03;
XYZ = XYZ(ind,:);
plane.ground = ransac(XYZ,plane.ground);

% update ceiling
if ~isempty(plane.ceiling)
    XYZ = sampling(Xw,Yw,imd,'upperHalf');
    % collect datapoints that are close to the old plane to reduce search space
    dis = calcDistance(plane.ceiling, 'XYZ', XYZ);
    ind = dis < 0.03;
    XYZ = XYZ(ind,:);
    plane.ceiling = ransac(XYZ,plane.ceiling);
end

end

