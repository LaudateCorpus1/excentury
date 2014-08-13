function val = cmp_info(info1, info2)
% excentury.core.CMP_INFO: Compare objects information.
%
% Return true if they have the same type of information, false
% otherwise.
%
    if info1{1} ~= info2{1}
        val = 0;
        return;
    end
    switch info1{1}
        case 'S'
            val = strcmp(info1{2}, info2{2}); 
        case 'W'
            val = 1;
        case 'T'
            val = excentury.core.cmp_info(info1{2}, info2{2});
        otherwise
            val = info1{2} == info2{2};
    end
end
