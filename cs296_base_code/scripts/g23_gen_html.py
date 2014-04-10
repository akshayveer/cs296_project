#!/usr/bin/env python3
css='<style>\nbody{margin: 0 auto;border: dotted grey;border-radius: 20px 0px 20px 0px;width:80%;padding : 20px;font-family:arial;font-size: 18px;letter-spacing: 2px;}\n\
		img{width:600px;height:600px;padding-left:25%;padding-right:25%;}\n\
		h1{color: #ff3366;text-align:center;font-family:"lucida sans"}\n\
		h2{text-align:center;font-family:"lucida sans";color: #00a900;}\n\
		h3{text-align:center;font-family:"lucida sans";color: #00a990;}\n</style>';
authors="";
tval=0;
texstream=open("../doc/g23_projectReport.tex","r");
htmlfile=open("../doc/g23_projectreport.html","w");
for line in texstream:
	line=line.strip();
	nline=line.lower();
	if(nline=="\\begin{document}"):
		htmlfile.write("<!doctype html>\n<html>\n<head>\n");
	elif(nline.find("\\author")!=-1 or tval==1):
		if(tval==0):
			line=line.strip("\\");
			i=line.find("{")+1;
			authors+=line[i:len(line)];
			tval+=1;
		elif(tval==1):
			if(line.find("\\and")!=-1):
				line=line.strip('\\and');
				authors+=(line+"\n<br>\n");
			elif(line.find("}")!=-1):
				tval+=1;
			else:
				line=line.strip("\\");
				#line=line.strip(",");
				authors+=("\t"+line);
	elif(nline.find("\cite")!=-1 or nline.find("\caption")!=-1):
		continue;
	elif(nline=="%biblography"):
		htmlfile.write("<h2>Authors</h2>"+authors+"\n</body>\n</html>");
		htmlfile.close();
		break;
	elif(nline.find("\\includegraphics")!=-1):
		i=line.find("{")+1;
		st=line[i:len(line)-1];
		st=st.strip();
		if(st=="release.png" or st=="debug.png" or st=="design.jpg" or st=="final.jpg"):
			htmlfile.write("<img src='"+st+"'></img>\n");
		else:
			htmlfile.write("<img src='"+"1"+st+"'></img>\n");
	elif(nline.find("\\title")!=-1):
		i=line.find("{")+1;
		st=line[i:len(line)-1];
		htmlfile.write("<title>"+st+"</title>\n"+css+"\n</head>\n<body><h1 style='font:ubuntu';color:#cc0033'>CS296 Project : Crane Arm Simulation</h1>\n");
	elif(nline.find("\\section")!=-1):
		i=line.find("{")+1;
		st=line[i:len(line)-1];
		htmlfile.write("<h1>"+st+"</h1>\n");
	elif(nline.find("\\subsection{")!=-1):
		i=line.find("{")+1;
		st=line[i:len(line)-1];
		htmlfile.write("<h2>"+st+"</h2>\n");
	elif(nline.find("\\subsubsection{")!=-1):
		i=line.find("{")+1;
		st=line[i:len(line)-1];
		htmlfile.write("<h3>"+st+"</h3>\n");
	elif(nline.find("{figure}")!=-1 or line.find("\\centering")!=-1 or line.find("\\maketitle")!=-1 or line.find("\\include")!=-1 or line.find("\\usepackage")!=-1 or line.find("\\documentclass")!=-1 or line.find("\\font")!=-1 or line.find("\\date")!=-1):
		continue;
	else:
		line=line.strip('\\');
		line=line.strip();
		line=line.strip('\\');
		if(line.find("1")!=-1 or (line.find("2")!=-1 and line.find("2D")==-1) or line.find("3")!=-1 or line.find("4")!=-1 or line.find("5")!=-1 or line.find("6")!=-1 or line.find("7")!=-1):
			htmlfile.write(line+"\n<br>");
		elif(line!=""):
			htmlfile.write(line+"\n");
		else:
			htmlfile.write(line+"\n");
