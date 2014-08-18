% util.SCALE_ARRAY was generated on Sat Jan 04, 2014 08:39:29 PM by xcpp 
% 
%     scale a one dimentional array.
% 
%     parameters:
% 
%       `v`: the array to be scaled.
%       `s`: the scalar factor.
%     
function varargout = scale_array(v, s, varargin)
    tdump = excentury.dump.textdumper;
    tdump.dump(v, 'v', {'T', {'R', '8'}});
    tdump.dump(s, 's', {'R', '8'});
    in_str = tdump.close;
    len_in = length(in_str);
    [~, out_str] = util.scale_array_mex(len_in, in_str);
    [val, order] = excentury.load.textparser(out_str).parse;
    if isempty(varargin)
        nout = length(order);
        varargout = cell(1, nout);
        for num=1:nout;
            varargout{num} = val(order{num});
        end
    else
        varargout{1} = val;
    end
end
