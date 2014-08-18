.. _excentury:

******************
What is excentury?
******************

Excentury is a collection of libraries written in several languages
to enable to the easy integration of C++ to scripting languages. By
using the excentury formats we can adapt or create new C++ code and
adapt it to computational languages such as Python and MATLAB.

Motivation
==========

Scripting languages give us many advantages: faster development,
extensive libraries and an overall easy of use. They are great tools
and can help individuals with no programming experience to get
started learning how to provide instructions to a machine. They allow
us to explore ideas relatively quick without spending too much time
dealing with compiler errors and many other problems that arise from
low level languages.

The main disadvantage is that their execution is slow compared to the
execution done by those compiled to machine code. Many scripting
languages offer support to adapt low level code, thus allowing you to
gain speed in your scripts. Learning how to do this is usually no
easy task since it requires the user to be familiar with the low
level language and the process to create the library is usually not
an easy one.

To see why sometimes it is convenient to switch to low level
languages we will explore the Lotka-Volterra_ model in MATLAB using
the `Gillespie algorithm`_.

.. _lotka-Volterra: http://en.wikipedia.org/wiki/Lotka%E2%80%93Volterra_equation
.. _Gillespie algorithm: http://en.wikipedia.org/wiki/Gillespie_algorithm


Stochastic Simulation Algorithm
===============================

In the Lotka-Volterra_ model we explore the dynamics of a predator
and prey populations. We assume that the populations interact through
four events. Each of these events is associated with a propensity
function ``a[i]``. The propensity functions gives us the probability
that the i-th event occurs during the next infinitesimal interval
``[t, t+dt]``, this probability is ``a[i]*dt``. Here we denote the
prey population with ``x`` and the predator population with ``y``.

The events are the following:

#. Birth of prey: ``a[1](x, y) = A*x``
#. Death of prey due to encounter with predator: ``a[2](x, y) = B*x*y``
#. Birth of predator due to prey consumption: ``a[3](x, y) = C*x*y``
#. Death of predator: ``a[4](x, y) = D*y``

As seen from the propensity functions mentioned in the events we see
that the prey population increases at a rate proportional to its size
and that predation is proportional to the rate at which the predators
and the prey meet. Similarly for the predator, its growth is
proportional to the rate to its encounter with the prey and its death
rate is proportional to its size.

To perform an stochastic simulation let us assume that ``t`` is the 
time when the last event was seen. Now must answer the following:

#. *How long goes the system has to wait until the next event occurs?* 
#. *What event takes place?*

The answer to the first question is a random number :math:`\tau` from
an exponential distribution of mean equal to the reciprocal of the
sum of the propensity functions evaluated at time ``t``. The event
that takes place after :math:`\tau` units of time is the i-th event
with probability equal to the fraction ``a[i]`` at time ``t``
occupies in the sum of the of the propensity function evaluated at
time ``t``, that is

.. math::

    P(i) = \frac{a[i](x(t),y(t))}{\sum_{k=1}^{4}a[k](x(t),y(t))}

The following MATLAB function generates realizations from the above
model.

.. code-block:: matlab
    :linenos:

    function [t, v] = lotka_volterra(A, B, C, D, x0, y0, num_points)

    % The change to the m-th population
    % due to the n-th event is denoted by
    % z(m, n).
    z = [1, -1, 0,  0;
         0,  0, 1, -1];

    t = zeros(1, num_points);
    v = zeros(2, num_points);
    t(1) = 0;
    v(:,1) = [x0, y0]';

    x = x0; 
    y = y0;
    for point=2:num_points
        % Evaluating propensity functions
        a = [A*x, B*x*y, C*x*y, D*y];
        a0 = sum(a);
        if a0 == 0
            break
        end
        % Time between events
        tau = log(1/rand)/a0;
        % Next event computation
        event = 0;
        prop_sum = 0;
        rand_num = rand*a0;
        while prop_sum < rand_num
            event = event + 1;
            prop_sum = prop_sum + a(event);
        end
        % Updating system
        x = x + z(1, event);
        y = y + z(2, event);
        % Storing point
        t(point) = t(point-1) + tau;
        v(:, point) = [x, y]';
    end

This function can be used to generate trajectories for the model. The
next figure shows some of the realizations that can be obtained by
running the above function.

.. figure:: _images/lotka_volterra_sims.png
   :alt: Lotka Volterra Simulations
   
   **Lotka Volterra stochastic realizations**: The parameters used
   for the simulation are as follows: ``A = 1, B = 0.001, C = 0.002``
   and ``D = 1``. The initial conditions are ``(x0, y0) = (1000,
   100)``. A total of 20 realizations of 50000 points were generated.
   In **A** we show the trajectories for the prey population. The
   predator population is shown in **B**. The red curve shows the
   solution to the deterministic model.

The MATLAB script is fairly simple and can be adapted to other
models. One downside is that, once we start to generate thousands or
millions or simulations in order to obtain desired statistics we find
that the interpreted code will run very slow compared to some code
written in C++.

Compiled Code
=============

When writing a program, we need a way of specifying inputs and
outputs. To write the same routine as above we will write a simple
program which takes no inputs. In this case, we will hard-code the
inputs into the program and save the data of one trajectory to a file.

.. code-block:: cpp
    :linenos:

    #include <random>
    #include <cstdio>

    int main() {
        // Function parameters
        double A = 1.0;
        double B = 0.001;
        double C = 0.002;
        double D = 1.0;
        int x0 = 1000;
        int y0 = 100;
        int num_points = 50000;

        // z[m][n] is the change to the m-th population
        // due to the n-th event.
        int z[2][4];
        z[0][0] = 1; z[0][1] = -1; z[0][2] = 0; z[0][3] =  0;
        z[1][0] = 0; z[1][1] =  0; z[1][2] = 1; z[1][3] = -1;

        // Random number generator
        std::default_random_engine generator;
        std::uniform_real_distribution<double> distribution(0.0,1.0);

        double x = x0;
        double y = y0;
    
        double a[4];
        double a0;
        double tau;
        int event;
        double prop_sum;
        double rand_num;

        double t[num_points];
        int v[2][num_points];
        t[0] = 0;
        v[0][0] = x0;
        v[1][0] = y0;

        for (int point = 1; point < num_points; ++point) {
            // Evaluating propensity functions
            a[0] = A*x;
            a[1] = B*x*y;
            a[2] = C*x*y;
            a[3] = D*y;
            // Sum of propensity functions
            a0 = 0;
            for (int i=0; i < 4; ++i) a0 += a[i];
            if (a0 == 0) {
                break;
            }
            // Time between events
            rand_num = distribution(generator);
            tau = log(1/rand_num)/a0;
            // Next event computation
            event = -1;
            prop_sum = 0;
            rand_num = distribution(generator)*a0;
            while (prop_sum < rand_num) {
                event = event + 1;
                prop_sum = prop_sum + a[event];
            }
            // Updating system
            x = x + z[0][event];
            y = y + z[1][event];
            // Storing point
            t[point] = t[point-1] + tau;
            v[0][point] = x;
            v[1][point] = y;
        }
        // Writing to file
        FILE* fp;
        fp = fopen("data.txt", "w");
        for (int point = 0; point < num_points; ++point) {
            fprintf(fp, "%f %d %d\n", t[point], v[0][point], v[1][point]);
        }
        fclose(fp);
    }

This program is very specialized, if we ever need to change the
parameter values, then we need edit the file, recompile the program
and run it. Furthermore, if we want to create a plot or analyze the
data we need to use MATLAB or Python. This requires us to load the
data first. This is no big issue, but as our data files become more
complicated we will find ourselves writing scripts to load the data
from the files into variables that we can manage. The data printed to
the file ``data.txt`` is easy to load into MATLAB with the following
commands.

.. code-block:: matlab

    load data.txt
    t = data(:, 1);
    x = data(:, 2);
    y = data(:, 3);
    plot(t, x);

This script was written only after the structure of ``data`` was
understood. If data was loaded as a 3 by 50000 matrix instead then we
would have to interpret the information differently.

Writing a C++ program is a complex task to start with. On top of that
we need to be able to provide inputs and outputs. The outputs in
particular need to be formatted in such a way that scripting
languages can understand.


Excentury
=========

Routines as the ones presented above gave rise to Excentury. The
first goal of Excentury was to create a data format which was easy to
code in C++ and MATLAB. The idea then was that a program would be
written in C++ and we would be able to save all the data into a file.
Then from MATLAB we would load it and proceed working on the data.

Eventually Python routines were written to read and write in the
excentury format. The next step was to skip writing to a file and
instead writing to a buffer so that MATLAB or Python would read
directly from it, thus eliminating the need to call C++ manually.

In the next section we present the ``lotka_volterra`` routine written
in the excentury format and show how it is call from C++, MATLAB and
Python.
