% util.GEN_TENSORS was generated on Sat Jan 04, 2014 08:39:28 PM by xcpp 
% 
%     Generate tensors of dimension 4.    
function varargout = gen_tensors(varargin)
    tdump = excentury.dump.textdumper;
    in_str = tdump.close;
    len_in = length(in_str);
    [~, out_str] = util.gen_tensors_mex(len_in, in_str);
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
