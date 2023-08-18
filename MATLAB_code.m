clc;
clear all;

% Initialize Arduino connection
global a; % Declare global variable
if ~isempty(instrfind)
    fclose(instrfindall);
    delete(instrfind);
end;
a = arduino;

% Configuration
interv = 200; % Data collection interval
init_time = 1; % Initial time for data collection

% Initialize variables
pH_data = 0;
temp_data = 40; % Initial temperature value in Celsius
distance_data = 0;

% Loop for data collection
while init_time <= interv
    % Read pH value
    voltage = readVoltage(a, 'A0') + 8;
    pH_value = (3.3 * voltage) + 8;
    pH_data = [pH_data, pH_value];
    
    % Read temperature value
    temperature = readDigitalPin(a, 'D12');
    temp_data = [temp_data, temperature];
    
    % Read distance value
    distance = readDigitalPin(a, 'D10');
    distance_data = [distance_data, distance];
    
    % Plotting
    subplot(3, 1, 1);
    plot(pH_data, 'LineWidth', 1);
    title('pH vs. Time', 'Color', [0.6 0.3 0.4], 'FontSize', 12);
    xlabel('Time, [s]', 'FontSize', 12.5);
    ylabel('pH', 'FontSize', 12.5);
    grid on;
    
    subplot(3, 1, 2);
    plot(temp_data, 'LineWidth', 1);
    title('Temperature vs. Time', 'Color', [0.6 0.3 0.4], 'FontSize', 12);
    xlabel('Time, [s]', 'FontSize', 12.5);
    ylabel('Temperature in Celsius', 'FontSize', 12.5);
    grid on;
    
    subplot(3, 1, 3);
    plot(distance_data, 'LineWidth', 1);
    title('Distance vs. Time', 'Color', [0.6 0.3 0.4], 'FontSize', 12);
    xlabel('Time, [s]', 'FontSize', 12.5);
    ylabel('Distance', 'FontSize', 12.5);
    grid on;
    
    init_time = init_time + 1;
    drawnow;
end
