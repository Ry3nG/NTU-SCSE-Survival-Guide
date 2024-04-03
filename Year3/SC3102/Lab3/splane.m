% Author: Chng Eng Siong
% date: Aug 2022

function splane(z,p)
    figure;           
    
    plot(real(z),imag(z),'ro','MarkerSize',10,'LineWidth',2);
    hold on;
    plot(real(p),imag(p),'bx','MarkerSize',10,'LineWidth',2);
    
    numDuplicates = 0;
    z = sort(z);
    for k = 2:length(z)
        if ((z(k) - z(k-1)) == 0)
            numDuplicates = numDuplicates + 1;        
        elseif (numDuplicates ~= 0)
            text(real(z(k-1))+.03,imag(z(k-1)),num2str(numDuplicates),...
                'Color','red','VerticalAlignment','bottom');
            numDuplicates = 0;        
        end
    end
    
    numDuplicates = 0;
    p = sort(p);
    for k = 2:length(p)
        if ((p(k) - p(k-1)) == 0)
            numDuplicates = numDuplicates + 1;        
        elseif (numDuplicates ~= 0)
            text(real(p(k-1))+.03,imag(p(k-1)),num2str(numDuplicates),...
                'Color','blue','VerticalAlignment','top');
            numDuplicates = 0;        
        end
    end
    
    xl = [xlim, ylim];
    limmax = max(abs(xl))*1.1; % give a little extra room
    xlim([-limmax limmax]);
    ylim([-limmax limmax]);
    plot([0 0],ylim,'k:',xlim,[0 0],'k:');
    axis square;
    
    xlabel('Real Axis');
    ylabel('Imaginary Axis');
    title('Zero-Pole Plot');
end