function info = get_info(obj)
% excentury.core.GET_INFO: Obtain an objects information
%
% Return a cell of two elements. The first element is the
% type of the object and the second denotes the size in bytes
% if the object is basic type (C, c, B, I, N, R), a name if
% its a struct (S), and info object if its a tensor (T) or
% no second element if its a string (W).
%
    kind = excentury.core.type(obj);
    switch kind
        case 'S'
            info = {'S', excentury.classname(obj)};
        case {'C', 'I', 'N', 'R'}
            tmp = whos('obj');
            if isa(obj, 'char')
                info = {kind, '1'};
            else
                info = {kind, sprintf('%d', tmp.bytes)};
            end
        case 'W'
            info = {'W'};
        case 'T'
            if isa(obj, 'cell')
                info = {'T', excentury.core.get_info(obj{1})};
            else
                info = {'T', excentury.core.get_info(obj(1))}; 
            end
        otherwise
            error('No info for this object.');
    end
end
