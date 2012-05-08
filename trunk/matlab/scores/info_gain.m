function [gain, threshold] = info_gain(var, Y, is_categorical, gain_measure)
%{
    Compute the information gain for a variable of a dataset
    Y - contains the class for each of the datapoints in var
    is_categorical - value of true if the variable is categorical. If false
                    the variable is considered continuous
    measure_name - 'gini' or 'entropy'
%}
    gain = 0;
    threshold = 0;
    if(gain_measure == InfoMeasure.gini)
        if(is_categorical)
            gain = nominal_gini(var,Y);
            threshold = 0;
        else
            [g, thr] = continuous_gini(var, Y);
            gain = g;
            threshold = thr;
        end
    elseif(gain_measure == InfoMeasure.entropy)
        if(is_categorical)
            gain = nominal_entropy(var, Y);
            threshold = 0;
        else
            [g, thr] = continuous_entropy(var, Y);
            gain = g;
            threshold = thr;
        end
    end
end

    function [gain] = nominal_gini(var, Y)
        %{
         gain(Y|var) = G(Y) - sum_j ( P(xj) * G(Y|xj) )
         G(Y) = total_gini = 1 - sum_k( fy^2)  --> fy = fraction of values of Y with class y  
         P(xj) = Probability of value xj for the variable var, estimated
         as fraction.
         G(Y|xj) - Gini impurity calulated over the values of Y
         corresponding to var == xj
        
          Each T(i,j) is the count of values i for each of the classes j.
          the table has rows = values in var and cols = classes in Y
        %}
        T = crosstab(var, Y);
        % fraction of points per of value of var
        A = sum(T,2); % A(k) is the sum of the values in row k
        n_points = sum(T(:));
        P = A / n_points;        
        % Fraction of each class in Y per value of the categorical variable var
        fyx = bsxfun(@rdivide, T, A);
        % sum pij^2 over the columns (values of var) 
        G = sum(fyx.^2, 2); % now G has the Gini impurity for each value xj
        G = 1 - P' * G;
        counts = sum(T,1); % counts of values per class
        gain = gini(counts) - G;
        

    end



    function [gain, threshold] = continuous_gini(X, Y)
        %{
            % Gini index for a continuous variable X.
                - X must be a column vector
                - Y is a nominal variable (column)
            The function finds the threshold (t) in X 
            that produces the  best split gain 
            gain = G(Y) - ( P(X<T)G(Y|X<t) + P(X>T)G(Y|X<t) )
        %}
        %fprintf('computing the continuous gini\n');
        
        gain = 0;
        threshold = 0;
        [sorted, indices] = sort(X);        
        % convert to indices the sorted version of Y. Indices allow fast
        % checking of valsY == sortedY(i) in the loop
        sortedY = grp2idx(Y(indices));
        rows = size(sorted, 1);
        counts = crosstab(sortedY);
        valsY = unique(sortedY);
        total_gini = gini(counts);
        n_values = size(valsY,1);
        if(n_values == 1)
            gain = 0;
            return 
        end        
        
        lower_contingency_table = zeros(1, n_values);
        upper_contingency_table = counts;
        for i = 1:rows-1
            % actualize table
            [comparison] = (valsY == sortedY(i));
            ind = find(comparison); % index where label == sortedY(i)
            lower_contingency_table(ind) = lower_contingency_table(ind)+1;
            upper_contingency_table(ind) = upper_contingency_table(ind)-1;
            P_low = 1. * i / rows;
            G_low = gini(lower_contingency_table);
            P_upp = 1. * (rows - i) / rows;
            G_upp = gini(upper_contingency_table);
            G = P_low * G_low + P_upp * G_upp;
            g = total_gini - G;
            if(g > gain)
                gain = g;
                threshold =sorted(i);
            end
        end
        %fprintf('the threshold is %f\n',threshold);
    end
        
            



    function [gain] = nominal_entropy(var, Y)
        %{
          gain(Y|var) = H(Y) - sum_j ( P(xj) * H(Y|xj) )
          H(Y) = log2(fy) * fy  --> fy = fraction of values of Y with class y  
          P(xj) = Probability of value xj for the variable var (estimated
          as fraction.
          H(Y|xj) - Entropy calulated over the values of Y with
    
          see nominal gini for comments
        %}
        T = crosstab(var, Y);
        A = sum(T,2);
        n_points = sum(T(:));
        P = A / n_points;        
        fyx = bsxfun(@rdivide, T, A);
        H = (-1) * sum(log2(fyx + eps) .* fyx, 2);
        H = P' * H;        

        counts = sum(T,1); % counts of values per class
        gain = entropy(counts) - H;
    end


    function [gain, threshold] = continuous_entropy(X, Y)   
    
        gain = 0;
        threshold = 0;
        [sorted, indices] = sort(X);        
        % convert to indices the sorted version of Y. Indices allow fast
        % checking of valsY == sortedY(i) in the loop
        sortedY = grp2idx(Y(indices));
        rows = size(sorted, 1);
        counts = crosstab(sortedY);
        valsY = unique(sortedY);
        total_H = entropy(counts);
        n_values = size(valsY,1);
        if(n_values == 1)
            gain = 0;
            return 
        end        
            
        lower_contingency_table = zeros(1, n_values);
        upper_contingency_table = counts;
        for i = 1:rows-1
            [comparison] = (valsY == sortedY(i));
            ind = find(comparison); % index where label == sortedY(i)
            lower_contingency_table(ind) = lower_contingency_table(ind)+1;
            upper_contingency_table(ind) = upper_contingency_table(ind)-1;
            P_low = 1. * i / rows;
            H_low = entropy(lower_contingency_table);
            P_upp = 1. * (rows - i) / rows;
            H_upp = entropy(upper_contingency_table);
            H = P_low * H_low + P_upp * H_upp;
            g = total_H - H;
            if(g > gain)
                gain = g;
                threshold =sorted(i);
            end
        end
    end
    
    function Ht = entropy(vals)
        fy = vals / sum(vals);
        Ht = (-1) * sum(fy .* log2(fy + eps));
    end
    
    function G = gini(vals)
        % gini impurity (don't use this
        % if you can vectorice computations of various variables)
        fy = vals / sum(vals);
        G = 1 - sum(fy.^2);
    end
  