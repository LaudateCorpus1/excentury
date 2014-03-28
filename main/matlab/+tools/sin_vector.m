% tools.SIN_VECTOR was generated on Fri Jan 24, 2014 02:01:46 AM by xcpp 
% 
%     Given a vector of values, it returns the sin of each of its
%     elements.
% 
%     parameters:
% 
%       `v`: input vector
%       `w`: input vector
%     
function varargout = sin_vector(v, w, varargin)
    tdump = excentury.dump.textdumper;
    tdump.dump(v, 'v', {'T', {'R', '8'}});
    tdump.dump(w, 'w', {'T', {'R', '8'}});
    in_str = tdump.close;
    len_in = length(in_str);
    [~, out_str] = tools.sin_vector_mex(len_in, in_str);
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
