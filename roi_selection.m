function [ roi, plane ] = roi_selection( imd, plane )

[Xw, Yw] = local2world(imd);

% update plane for every 10 frames
global timer

if isempty(timer)
    timer = 0; % init a timer
else 
    timer = timer + 1; % update timer
end

if timer > 15
    plane = updatePlane(Xw,Yw,imd,plane);
    timer = 0; % reset timer
end

% Ground plane removal (GPR)
roi_gpr = calcDistance(plane.ground, 'multiMaps', Xw, Yw, imd);
roi_gpr(roi_gpr < 0.05) = 0;
roi_gpr(roi_gpr ~= 0) = 1;

% Ceiling plane removal (CPR)
if ~isempty(plane.ceiling)
    roi_cpr = calcDistance(plane.ceiling, 'multiMaps', Xw, Yw, imd);
    roi_cpr(roi_cpr < 0.03) = 0;
    roi_cpr(roi_cpr ~= 0) = 1;
    roi = roi_gpr .* roi_cpr;
else
    roi = roi_gpr;
end

% Smooth roi
se = strel('square',5);
roi = imerode(roi,se);


end

