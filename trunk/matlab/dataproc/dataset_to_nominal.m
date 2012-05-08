function data = dataset_to_nominal(data, are_categorical)
    % Convert the columns of a dataset that are categorical data to
    % nominal variables
    % data - dataset
    % are categorical - A vector of boolean values. False if the col
    % in the dataset is not categorical, true if it is categorical
    names = data.Properties.VarNames;
    n = size(names,2);
    for i = 1:n
        if(are_categorical(i))
            name = char(names(i));
            data.(name) = nominal(data.(name));
        end
    end
end
