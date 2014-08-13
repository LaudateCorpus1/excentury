% util.XC_STRUCT was generated on Sun Jan 05, 2014 11:07:21 PM by xcpp
%
% Return an excentury.xc_strut object using the entries of the
% containers.Map provided by this package (util.xc_def).
%
% The following are equivalent:
%
%     p = excentury.xc_struct('classname', util.xc_def('classname'));
%
%     p = util.xc_struct('classname');
%
% The posible inputs are: 
%
%    Point
%
function obj = xc_struct(name)
    obj = excentury.xc_struct(name, util.xc_def(name));
end

