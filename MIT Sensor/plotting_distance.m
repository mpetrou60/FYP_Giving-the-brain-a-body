%-------------------------------------------------------------------------
% Project: FYP Giving the Brain a Body
% Authors: Maria N. Petrou
% Description: Convert recorded induced voltage data from Magnetic
%              Inductance Transmitter to distance to measure actuator
%              expansion.
% -------------------------------------------------------------------------

clc, clear, close all 

%% load data
load data.mat

%% plot 28 measurements possible from the device over 1200 frames
figure(1)
hold on
for i = 1:length(data(1,:))
    plot(data(:,i))
end
hold off
ylabel('Induced Voltage (V)')
xlabel('Sample Rate (Hz)')

%% convert to distance and plot
% 28 unique coil pairs: 1-2, 1-3, …, 1-8, 2-3, 2-4, …, 7-8,
% so isolate 1-2, 2-3, 3-4, 4-5, 5-6, 6-7, 7-8
% focus on first 5 sensors (because errors propagate and actuator was
% connected to first 2 so might as well look at these ones specifically.

% Convert the sensor measurement to distance
% predefined variables for induced voltage to distance conversion
a = 1663;
b = -0.9646;
c = 1.575;

% initial position
d1=data(1,:);

% translate all voltage values to distance using predefined equation
for i=1:28
    y(i) = a*(d1(1,i))^b + c;
end

% x co-ordinates
elmntX1=[0,y(1),y(2),y(1)+y(8)+y(14),y(1)+y(8)+y(14)+y(19)];

% y co-ordinate
elmntY1 = [0 0 0 0 0];

% plot initial distance so that it is always in the video
figure(2)
hold on
for i = 1:length(elmntX1)
    % plot initial points
    plot(elmntX1(i), elmntY1(i), 'k.','MarkerSize',50,'LineWidth', 2)
    xlim([0, 10])
    %     title('Plot of distance travelled by sensors')
    ylabel('Vertical Distance between sensors (cm)')
    xlabel('Horizontal Distance between sensors (cm)')
    xticks(1:10);
    set(gca,'FontSize',20)
end

% calculate distance for all moving points
for i=2:size(data,1)
    di=data(i,:);

    % This is the for loop that translates all the voltage values to distance
    for j=1:28
        y(j) = a*(di(1,j))^b + c;
    end

    % x co-ordinates
    elmntX1=[0,y(1),y(2),y(1)+y(8)+y(14),y(1)+y(8)+y(14)+y(19)];

    % y co-ordinate
    elmntY1 = [0 0 0 0 0];

    % plot a marker for each sensor  
    plotHandles1 = plot(elmntX1(1), elmntY1(1), 'r-o','MarkerSize',20,'LineWidth', 2);
    plotHandles2 = plot(elmntX1(2), elmntY1(2), 'r-o','MarkerSize',20,'LineWidth', 2);
    plotHandles3 = plot(elmntX1(3), elmntY1(3), 'r-o','MarkerSize',20,'LineWidth', 2);
    plotHandles4 = plot(elmntX1(4), elmntY1(4), 'r-o','MarkerSize',20,'LineWidth', 2);
    plotHandles5 = plot(elmntX1(5), elmntY1(5), 'r-o','MarkerSize',20,'LineWidth', 2);
    
    % plot position of each sensor for each sample
    drawnow
    
    % Clear the points of current sample
    delete(plotHandles1); 
    delete(plotHandles2); 
    delete(plotHandles3); 
    delete(plotHandles4); 
    delete(plotHandles5); 
end
hold off
