%range = [44000, 88000];
range = [1,4400];
%read = audioread('e1.wav', range);
read1 = audioread('trimmed.wav',range);
read1 = read1(:,1);
read1 = downsample(read1,2);
read1 = round(read1*256); %256 bc 8 bit resolution
%[C, L] = wavedec(read, 11, 'Haar');
bdps = 10; %beat detections per second
segments = bdps*(length(read1)/22000);

beats = zeros(9);

for i = 1:segments
    [C, L] = wavedec(read1, 11, 'Haar');
    [cd1,cd2,cd3,cd4,cd5,cd6,cd7,cd8,cd9,cd10,cd11] = detcoef(C, L,[1, 2, 3, 4,5,6,7,8,9,10,11]);
    
    if (max(abs(cd3)) >= 400)
        fprintf('there is a cd3 type beat at time %5.2f\n',(1/bdps)*i)
        beats(1) = 1;
    end
    if (max(abs(cd4)) >= 600)
        fprintf('there is a cd4 type beat at time %5.2f\n',(1/bdps)*i)
        beats(2) = 1;
    end
    if (max(abs(cd5)) >= 600)
        fprintf('there is a cd5 type beat at time %5.2f\n',(1/bdps)*i)
        beats(2) = 1;
    end
    if (max(abs(cd6)) >= 1000)
        fprintf('there is a cd6 type beat at time %5.2f\n',(1/bdps)*i)
        beats(2) = 1;
    end
    if (max(abs(cd7)) >= 1500)
        fprintf('there is a cd7 type beat at time %5.2f\n',(1/bdps)*i)
        beats(2) = 1;
    end
    if (max(abs(cd8)) >= 1800)
        fprintf('there is a cd8 type beat at time %5.2f\n',(1/bdps)*i)
    end
    if (max(abs(cd9)) >= 1800)
        fprintf('there is a cd9 type beat at time %5.2f\n',(1/bdps)*i)
    end
    if (max(abs(cd10)) >= 750)
        fprintf('there is a cd10 type beat at time %5.2f\n',(1/bdps)*i)
    end
    if (max(abs(cd11)) >= 750)
        fprintf('there is a cd11 type beat at time %5.2f\n',(1/bdps)*i)
    end
end
