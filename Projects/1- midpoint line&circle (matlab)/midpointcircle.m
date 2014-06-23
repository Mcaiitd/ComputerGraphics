function midpointcircle(h,k,r)
% midpointcircle(20,20,10)
%h=20;k=20;r=10;
    x=0;
    y=r;
    p=(1-r);
    im_mat = ones(100,100);
    flag = true;

    while flag
        im_mat(k+y,h+x)=0;
        im_mat(k+x,h+y)=0;
        im_mat(k-x,h+y)=0;
        im_mat(k-y,h+x)=0;
        im_mat(k-y,h-x)=0;
        im_mat(k-x,h-y)=0;
        im_mat(k+x,h-y)=0;
        im_mat(k+y,h-x)=0;

        x=x+1;

        if (p<0)
            p = p+(2*x)+1;
        else
            y = y-1;
            p = p+(2*(x-y))+1;
        end

        if x>y
            flag = false;
        end
    end
    imshow(im_mat);
end
