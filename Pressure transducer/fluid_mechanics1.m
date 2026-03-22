l = 10e-2;       %  total channel length (m)
N = 10;       % number of bladders
r_1 = 50e-6;     % connecting channel radius (m)
r_2 = 1e-3;      % bladder radius (m)
w = 5e-6;        % uniform wall thickness (m)
mu = 18.5e-6; % fluid viscosity (Pa.sec)
E = 10;       % material elasticity modulus of pds (MPa) (=100bar)
T_f = 5;      % calculations performed for period (s)
x_fend = l;      % closed end to block flow
c = 3e-5;     % compliance coefficient value
p_atm = 1.1035; % atmospheric pressure (bar) 

a = 1/(8*pi()*mu);
b = (pi()*r_2^2)^2;

i = 1;

for p = 2:0.1:0 % pressure (bar)
%     if p ~= 2
        x_f1 = b*(1 + (p*r_2)/(E*w))^4;
%     else 
%         x_f1 = x_fend;
%     end

    x_f(i) = a*(p+p_atm)*x_f1;
    pressure(i) = p;
    i = i + 1;
    
end

x_f = x_f.*10e2;

plot(x_f, pressure)




