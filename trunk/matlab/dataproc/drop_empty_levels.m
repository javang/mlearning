function [x] = drop_empty_levels(var)

if(~isa(var, 'nominal'))
    exception = MException('drop_empty_levels:isnominal', ...
       'A nominal variable is expected');
    throw(exception)
end

x = var;
[counts, labels] = summary(var);
n = size(counts);
for i =1:n
    if(counts(i) == 0)
        x = droplevels(var, char(labels(i)))
    end
end