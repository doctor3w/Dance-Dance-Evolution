%range = [44000, 88000];
%read = audioread('e1.wav', range);
read = audioread('trimmed.wav');
%fqs = [50,100,500,1000,2500,5000,7500,10000,12500,15000,17500,20000];
%read = sinSFi(fqs, 44000*length(fqs),'time',1);
read = read(:,1);
read = downsample(read,2);
read = round(read*256);
[C, L] = wavedec(read, 11, 'Haar');

subplot(6,2,1)
plot(read)
title('Original signal')

[cd1,cd2,cd3,cd4,cd5,cd6,cd7,cd8,cd9,cd10,cd11] = detcoef(C, L,[1, 2, 3, 4,5,6,7,8,9,10,11]);
%[cd1,cd2,cd3,cd4,cd5,cd6,cd7,cd8,cd9,cd10,cd11] = appcoef(C, L,[1, 2, 3, 4,5,6,7,8,9,10,11]);

subplot(6,2,2)
plot(abs(cd1))
title('cd1')

subplot(6,2,3)
plot(abs(cd2))
title('cd2')

subplot(6,2,4)
plot(abs(cd3))
title('cd3')

subplot(6,2,5)
plot(abs(cd4))
title('cd4')

subplot(6,2,6)
plot(abs(cd5))
title('cd5')

subplot(6,2,7)
plot(abs(cd6))
title('cd6')

subplot(6,2,8)
plot(abs(cd7))
title('cd7')

subplot(6,2,9)
plot(abs(cd8))
title('cd8')

subplot(6,2,10)
plot(abs(cd9))
title('cd9')

subplot(6,2,11)
plot(abs(cd10))
title('cd10')

subplot(6,2,12)
plot(abs(cd11))
title('cd11')