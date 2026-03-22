%-------------------------------------------------------------------------
% Project: FYP Giving the Brain a Body
% Authors: Maria N. Petrou
% Description: Calculate pressure using fluid mechanics equations
% -------------------------------------------------------------------------

% long-wave approximation
r_1 = 0.9255; % mm
r_2 = 2.584; % mm
N = 6; % number of repeating cells

sum_part = 0;

for x = 1:70 % x
    for i = 1:N
        a1 = (2*i - 1)/N;
        a2 = i/N;
        sum_part = sum_part + ((r_2 - r_1)*(myHeaviside(x,a1) - myHeaviside(x,a2)));
    end
    r_s(x) = r_1 + sum_part;
    sum_part = 0;
end

plot(r_s)

function [out] = myHeaviside(x,a)
% heaviside function H(x-a)
if x < a
    out = 1;
elseif x == a
    out = 1/2;
else
    out = 0;
end

end