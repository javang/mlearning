function test_suite = tests_for_information_gain
initTestSuite;

    function test_discrete_gini
        Y = nominal({'a','a','a','a','a','a'});
        X = [ 1 2 3 4 5 6 ];
        g = info_gain(X, Y, true, InfoMeasure.gini);
        epsilon = 1e-3;
        assertElementsAlmostEqual(g, 0, 'relative', 0.01);    
        Y = nominal([ 0 0 0 1 1 1]');
        X = [ 3 3 3 4 4 4];
        g = info_gain(X, Y, true, InfoMeasure.gini);
        assertElementsAlmostEqual(g, 0.5, 'relative', 0.01);    
        X = [ 3 4 3 4 4 4];
        g = info_gain(X, Y, true, 'gini');
        assertTrue(g< 0.5, 'Expected information gain lower than 0.5');    
        

    function test_continuous_gini
        Y = nominal({'a','a','a','a','a','a'});
        X = [3.23, 3.89, 1.34234, 3.435, 2.34348, 0.2131]';
        [g, threshold] = info_gain(X, Y, false, InfoMeasure.gini);
        assertElementsAlmostEqual(g, 0, 'relative', 0.01);    
        Y = nominal([1 1 0 1 0 0]');
        [g, threshold] = info_gain(X, Y, false, InfoMeasure.gini);
        assertElementsAlmostEqual(g, 0.5, 'relative', 0.01);    
        Y = nominal([ 0 1 0 1 1 1]');
        [g, threshold] = info_gain(X, Y, false, InfoMeasure.gini);
        assertTrue(g< 0.5, 'Expected information gain lower than 0.5');    

      function test_discrete_entropy
        Y = nominal({'a','a','a','a','a','a'});
        X = [ 1 2 3 4 5 6 ];
        g = info_gain(X, Y, true, InfoMeasure.entropy);
        epsilon = 1e-3;
        assertElementsAlmostEqual(g, 0, 'relative', 0.01);    
        Y = nominal([ 0 0 0 1 1 1]');
        X = [ 3 3 3 4 4 4];
        g = info_gain(X, Y, true, InfoMeasure.entropy);
        assertElementsAlmostEqual(g, 1, 'relative', 0.01);    
        X = [ 3 4 3 4 4 4];
        g = info_gain(X, Y, true, InfoMeasure.entropy);
        assertTrue(g< 1, 'Expected information gain lower than 0.5');    

        
    function test_continuous_entropy
        Y = nominal({'a','a','a','a','a','a'});
        X = [3.23, 3.89, 1.34234, 3.435, 2.34348, 0.2131]';
        [g, threshold] = info_gain(X, Y, false, InfoMeasure.entropy);
        assertElementsAlmostEqual(g, 0, 'relative', 0.01);    
        Y = nominal([1 1 0 1 0 0]');
        [g, threshold] = info_gain(X, Y, false, InfoMeasure.entropy);
        assertElementsAlmostEqual(g, 1, 'relative', 0.01);    
        Y = nominal([ 0 1 0 1 1 1]');
        [g, threshold] = info_gain(X, Y, false, InfoMeasure.entropy);
        assertTrue(g< 1, 'Expected information gain lower than 1');    
