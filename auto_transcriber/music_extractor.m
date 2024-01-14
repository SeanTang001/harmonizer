clear
d = readtable("serial.log");
data = table2array(d);
a = [];
b = [];
for i =1:size(data)
    ab = fix(data(i)/10^fix(log10(data(i))));
    if(ab==1)
        a=[a,mod(data(i),10^fix(log10(data(i))))];
    else
        b=[b,mod(data(i),10^fix(log10(data(i))))];
    end
end

a = clean(a);
b = clean(b);

abmin = min(a(1),b(1));
a(1) = a(1) - abmin;
b(1) = b(1) - abmin;

bpm(a,b);

function data = clean(data)
    i = 1;
    [c,s] = size(data);

    while(i<s)
        if(data(1,i)<100&&i>1)
            %fprintf(" fuck %d ",data(1,i));
            data(1,i-1) = data(1,i-1)+data(1,i);
            data(1)=[];
            s = s-1;
        else
            i=i+1;
        end
    end
end

function plotdata(data,m)
    vals = cumsum(data);
    scatter(vals,m*ones(size(vals)));
    ylim([0 2]);
    hold on;
end

function bpm(data1,data2)
    plotdata(data1,1.5);
    plotdata(data2,1.4);
    [c,s] = size(data1)
    for i = 1:s
        fprintf("%d \n",data1(1,i));
    end
    %figure;

    %start
    scan(900,900,1000000,data1,data2,[],[]);
    %fprintf("%d %.2f\n",tempo,rate);
end
function scan(rollingbpm,besttempo,besterror,data1,data2,bestbeats1,bestbeats2)
    fprintf("attmepting tempo of %d\n",rollingbpm);
    onbeat = 0;
    totalbeat = 0;
    totalerror = 0;
    totalcount = 0;
    offcount = 0;
    beats1 = [];
    [c,s] = size(data1);
    

    for i = 1:s
        totalbeat = totalbeat+1;

        if(totalcount==0&&mod(round(16*data1(i)/rollingbpm),16)<=2)
            inc = round(16*data1(i)/rollingbpm)-mod(round(16*data1(i)/rollingbpm),16); 
        else
        inc = 2*round(16*data1(i)/(2*rollingbpm));
        end

        error = (abs((16*data1(i)/rollingbpm)-inc)/16*rollingbpm/600)^0.5;
        fprintf("error %.3f\n",error);
        totalcount = totalcount + inc;
        totalerror = totalerror+error;

        if(mod(mod(totalcount,16),4)~=0)
            offcount= offcount+1;
            totalerror = totalerror + offcount*error;
        end
        if(mod(mod(totalcount,16),8)~=0)
            totalerror = totalerror + offcount*error;
        end
        if(mod(totalcount,16)==0)
            totalerror = totalerror - offcount*error;
        end
        if(inc==8||inc==16)
            totalerror = totalerror - offcount*error;
        end
        fprintf("%.2f %d\n",error,offcount);
        beats1 = [beats1 inc]

    end

    totalcount = 0;

    beats2 = [];
    [c,s] = size(data2);

    for i = 1:s
        totalbeat = totalbeat+1;

        if(totalcount==0&&mod(round(16*data2(i)/rollingbpm),16)<=2)
            inc = round(16*data2(i)/rollingbpm)-mod(round(16*data2(i)/rollingbpm),16); 
        else
        inc = 2*round(16*data2(i)/(2*rollingbpm));
        end        
        error = (abs((16*data2(i)/rollingbpm)-inc)/16*rollingbpm/600)^0.5;
        fprintf("error %.3f\n",error);
        totalcount = totalcount + inc;
        totalerror = totalerror+error;

        %if(mod(totalcount,16)==1)
        %   totalerror = totalerror+(inc-16)*error^2;
        %end
        if(mod(mod(totalcount,16),4)~=0)
            offcount= offcount+1;
            totalerror = totalerror + offcount*error;
        end
        if(mod(mod(totalcount,16),8)~=0)
            totalerror = totalerror + offcount*error;
        end
        if(mod(totalcount,16)==0)
            totalerror = totalerror - offcount*error;
        end
        if(inc==8||inc==16)
            totalerror = totalerror - offcount*error;
        end
        fprintf("%.2f %d\n",error,inc);
        beats2 = [beats2 inc]

    end

    tempo = rollingbpm;
    rate = onbeat/totalbeat;
    fprintf("totalerror of  %.3f\n",totalerror/totalbeat);
    fprintf("%d %.2f\n",tempo,rate);
    if(totalerror/totalbeat<besterror)
        besterror = totalerror/totalbeat;
        besttempo = tempo;
        bestbeats1 = beats1;
        bestbeats2 = beats2;
    end
    if(tempo>=300&&tempo<=1000)
        scan(tempo-1,besttempo,besterror,data1,data2,bestbeats1,bestbeats2);
    else
       fprintf("final %.3f %.3f\n",60000/besttempo,besterror);
       t = 0:max(sum(data1),sum(data2))/besttempo;
       scatter(besttempo*t,ones(size(t)));
       bestbeats1 = bestbeats1
       bestbeats2 = bestbeats2
       scatter(besttempo*(cumsum(bestbeats1)/16),0.8*ones(size(bestbeats1)));
       scatter(besttempo*(cumsum(bestbeats2)/16),0.7*ones(size(bestbeats2)));

       dataz = {60000/besttempo,{bestbeats1,bestbeats2}};
       save data.mat dataz;
    end    
end
