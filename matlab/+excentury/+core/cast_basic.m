function obj = cast_basic(obj, kind)
% excentury.core.CAST_BASIC: Cast object to a basic datatype
%
%   Transform the object to another basic object. 
%   The allowed values for kind are:
%
%         char, 'C1' ==> char  
%         byte, 'I1' ==> int8
%        ubyte, 'N1' ==> uint8
%        short, 'I2' ==> int16 
%          int, 'I4' ==> int32 
%         long, 'I8' ==> int64
%       ushort, 'N2' ==> uint16 
%         uint, 'N4' ==> uint32 
%        ulong, 'N8' ==> uint64
%        float, 'R4' ==> single 
%       double, 'R8' ==> double
%
    switch kind
        case {'char', 'C1'}
            obj = char(obj);
        case {'byte', 'I1'}
            obj = int8(obj);
        case {'ubyte', 'N1'}
            obj = uint8(obj);
        case {'short', 'I2'}
            obj = int16(obj);
        case {'int', 'I4'}
            obj = int32(obj);
        case {'long', 'I8'}
            obj = int64(obj);
        case {'ushort', 'N2'}
            obj = uint16(obj);
        case {'uint', 'N4'}
            obj = uint32(obj);
        case {'ulong', 'N8'}
            obj = uint64(obj);
        case {'float', 'R4'}
            obj = single(obj);
        case {'double', 'R8'}
            obj = double(obj);
        otherwise
            error('invalid kind');
    end
end
