function midpointline(x1,y1,x2,y2)
    im_mat = ones(100,100);
    dy = y2-y1;
    dx = x2-x1;
           
    rot=0;
    if(dy>dx)
        
            rot = 1;
           temp = y1; y1 = x1; x1=temp;
           temp = y2; y2 = x2; x2=temp;
               dy = y2-y1;
    dx = x2-x1;
        
    end
    
    
    
    p=2*dy-dx;
    im_mat(y1, x1)=0;
    y=y1;
    for x=x1+1:x2	
        if(p > 0)
            y = y+1;
            im_mat(y, x)=0;
            p = p+(2*dy-2*dx);
        else
            im_mat(y, x)=0;
            p = p+2*dy;
        end
    end
    
%     imshow(im_mat);
%     imgMirror = flipdim(img,2);

if(rot==1)
   
        im_mat = im_mat';
        
end
    imshow(flipdim(im_mat,1)); % flips the axis so that +ve x and y direction are adjusted.
    
end