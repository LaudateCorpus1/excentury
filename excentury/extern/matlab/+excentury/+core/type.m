function xctype = type(obj)
% excentury.core.TYPE: Obtain a character denoting the type
%
% The type can be one of the following:
%
%   'C', 'I', 'N', 'R', 'S', 'T', 'W'.
%
% C: Character object (char)
% I: An integer
% N: Natural number (unsigned integer)
% R: Real number (float, double)
% S: Structure
% T: Tensor
% W: Word (string)
%
    switch class(obj)
        case 'char'
            if length(obj) > 1
                xctype = 'W';
                return
            else
                xctype = 'C';
            end
        case {'int64', 'int32', 'int16', 'int8'}
            xctype = 'I';
        case {'uint64', 'uint32', 'uint16', 'uint8'}
            xctype = 'N';
        case {'single', 'double'}
            xctype = 'R';
        case 'cell'
            xctype = 'T';
            return
        otherwise
            xctype = 'S';
            return
    end
    if length(obj) > 1
        xctype = 'T';
    end
end
