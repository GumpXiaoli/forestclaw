s = 0;
axis([-s 2+s -s 2+s])
daspect([1 1 1]);

yrbcolormap;
showpatchborders(1:6);
% hidepatchborders;
delete(get(gca,'title'));
caxis([0 1]);


shg;

NoQuery = 0;
prt = false;
if (prt)
  filename = framename(Frame,'swirl0000','png');
  print('-dpng',filename);
end;

clear afterframe;
clear mapc2m;
clear mapc2m_squareddisk;
clear mapc2m_pillowdisk;

