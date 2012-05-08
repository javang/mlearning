function test_suite =tests_for_random_forest
initTestSuite;

    function test_forest
        clear;
        randseed;
        load('training.mat');

        % known values
        Y = nominal(training.species);
        training.species = [];
        ddata = double(training);
        are_categorical = [false false false false];
        RF = RandomForest(10);
        RF.train(ddata, Y, are_categorical);  

        load('test.mat');
        test_class = nominal(test.species);
        class_values = unique(test_class);
        dtest = double(test);
        
        class_indices = RF.predict(dtest);
        predictions = class_values(class_indices);   
        [precision, recall, f] = fscore(test_class, predictions);
        % this asserts are approximated based on previous runs
        assertTrue(precision > 0.8);
        assertTrue(recall > 0.8);
        
        %{
        % compare with a tree
        T = DecisionTree;       
        T.train(ddata, Y, are_categorical);  
        prediction_indices = T.predict(dtest);
        predictions = class_values(prediction_indices)'   
        [precision, recall, f] = fscore(test_class, predictions)
        %}