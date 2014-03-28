% util.XC_DEF was generated on Sun Jan 05, 2014 11:07:21 PM by xcpp
%
% Provides the definition of the objects that the functions in
% this package return. Provide no arguments to obtain the whole
% map. If you need only one definition then provide the key.
%
function obj = xc_def(varargin)
    persistent defs;
    if isempty(defs)
        defs = containers.Map;
        defs('Point') = { ...
            {'x', {'R', '8'}}, ...
            {'y', {'R', '8'}}, ...
        };
    end
    if isempty(varargin)
        obj = defs;
    else
        obj = defs(varargin{1});
    end
end
