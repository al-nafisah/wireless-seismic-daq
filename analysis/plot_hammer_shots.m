% Hammer-shot comparison: Geophysics department recorder vs. this prototype.
% Run from the analysis folder. Writes ../media/hammer-shots.png
clear
close all

shots = [4 7 6];                        % shot number (see data/hammer-shots/shots.csv)
refs  = [58 61 60];                     % matching reference file
links = {'10 m XBee link', '25 m XBee link', '50 m XBee link'};
window = [-20 160];                     % ms around the first break

blue   = [42 120 214]/255;              % this prototype
orange = [235 104 52]/255;              % reference recorder
ink    = [0.04 0.04 0.04];

fig = figure('Color', 'w', 'Position', [0 0 1500 560]);
tl = tiledlayout(2, 3, 'TileSpacing', 'compact', 'Padding', 'compact');
for k = 1:3
    [r, fr] = read_seg2(sprintf('../data/hammer-shots/reference/%d.dat', refs(k)), 1);
    [x, fx] = read_shot(sprintf('../data/hammer-shots/shot%d.txt', shots(k)));

    nexttile(k)
    trace(r, fr, window, orange)
    title(links{k}, 'FontWeight', 'normal', 'Color', ink)
    if k == 1, ylabel({'Geophysics recorder', sprintf('(%.0f samples/s)', fr)}), end

    nexttile(k + 3)
    trace(x, fx, window, blue)
    xlabel('Time from first break (ms)')
    if k == 1, ylabel({'This prototype', sprintf('(%.0f samples/s)', fx)}), end
end
title(tl, 'Same hammer shot, two recorders', 'FontSize', 14, 'Color', ink)
exportgraphics(fig, '../media/hammer-shots.png', 'Resolution', 150)

function trace(x, fs, window, color)
% Plot a trace normalized to its peak, with t = 0 at the first break.
x = x - median(x(1:20));
x = x / max(abs(x));
t = ((0:numel(x)-1) - find(abs(x) > 0.2, 1)) / fs * 1000;
plot(t, x, 'Color', color, 'LineWidth', 1.2)
xlim(window), ylim([-1.1 1.1])
set(gca, 'Color', 'w', 'Box', 'off', 'YTick', [], 'XGrid', 'on', 'GridAlpha', 0.12, ...
    'FontSize', 11, 'XColor', [0.32 0.32 0.31], 'YColor', [0.32 0.32 0.31])
end

function [x, fs] = read_shot(file)
% Serial log from the prototype: one sample (mV) per line, with the
% recording time printed after each run. Uses the last run in the file.
lines = strtrim(splitlines(fileread(file)));
v = str2double(lines);
k = find(startsWith(lines, 'Total Time'), 1, 'last');
T = sscanf(lines{k}, 'Total Time (in milli-seconds): %f') / 1000;
e = find(~isnan(v(1:k)), 1, 'last');
b = find(isnan(v(1:e)), 1, 'last') + 1;
x = v(b:e);
fs = numel(x) / T;
end

function [x, fs] = read_seg2(file, ch)
% Minimal SEG-2 reader for the reference files: float32 samples,
% 0.125 ms sample interval (both fixed in these files' headers).
fid = fopen(file, 'r', 'l');
fseek(fid, 6, 'bof');
n = fread(fid, 1, 'uint16');
fseek(fid, 32, 'bof');
ptr = fread(fid, n, 'uint32');
fseek(fid, ptr(ch) + 2, 'bof');
bs = fread(fid, 1, 'uint16');
fread(fid, 1, 'uint32');
ns = fread(fid, 1, 'uint32');
fseek(fid, ptr(ch) + bs, 'bof');
x = fread(fid, ns, 'float32');
fclose(fid);
fs = 8000;
end
