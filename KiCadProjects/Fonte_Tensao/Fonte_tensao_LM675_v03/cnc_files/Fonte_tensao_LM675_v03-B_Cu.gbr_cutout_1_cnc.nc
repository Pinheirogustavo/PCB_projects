(G-CODE GENERATED BY FLATCAM v8.994 - www.flatcam.org - Version Date: 2020/11/7)

(Name: Fonte_tensao_LM675_v03-B_Cu.gbr_cutout_1_cnc)
(Type: G-code from Geometry)
(Units: MM)

(Created on quinta, 22 junho 2023 at 19:02)

(This preprocessor is the default preprocessor used by FlatCAM.)
(It is made to work with MACH3 compatible motion controllers.)

(TOOL DIAMETER: 1.0 mm)
(Feedrate_XY: 60.0 mm/min)
(Feedrate_Z: 60.0 mm/min)
(Feedrate rapids 1500.0 mm/min)

(Z_Cut: -1.6 mm)
(DepthPerCut: 0.2 mm <=>8 passes)
(Z_Move: 2.0 mm)
(Z Start: None mm)
(Z End: 15.0 mm)
(X,Y End: None mm)
(Steps per circle: 64)
(Preprocessor Geometry: default)

(X range:   -1.7573 ...   88.1900  mm)
(Y range:   -1.9793 ...   99.7953  mm)

(Spindle Speed: 1000.0 RPM)
G21
G90
G94

G01 F60.00

M5
G00 Z5.0000
G00 X0.0000 Y0.0000
(T1)
(M6  )  
(MSG, Change to Tool Dia = 1.0000)
(M0)
G00 Z5.0000

M03 S1000.0
G01 F60.00
G00 X85.6900 Y-1.9793
G01 F60.00
G01 Z-0.2000
G01 F60.00
G01 X0.7427 Y-1.9793
G01 X0.4976 Y-1.9673
G01 X0.2550 Y-1.9313
G01 X0.0170 Y-1.8717
G01 X-0.2140 Y-1.7890
G01 X-0.4358 Y-1.6841
G01 X-0.6462 Y-1.5580
G01 X-0.8433 Y-1.4118
G01 X-1.0251 Y-1.2471
G01 X-1.1898 Y-1.0653
G01 X-1.3360 Y-0.8682
G01 X-1.4621 Y-0.6578
G01 X-1.5670 Y-0.4360
G01 X-1.6497 Y-0.2050
G01 X-1.7093 Y0.0330
G01 X-1.7453 Y0.2756
G01 X-1.7573 Y0.5207
G01 X-1.7573 Y97.2953
G01 X-1.7453 Y97.5404
G01 X-1.7093 Y97.7830
G01 X-1.6497 Y98.0210
G01 X-1.5670 Y98.2520
G01 X-1.4621 Y98.4738
G01 X-1.3360 Y98.6842
G01 X-1.1898 Y98.8813
G01 X-1.0251 Y99.0631
G01 X-0.8433 Y99.2278
G01 X-0.6462 Y99.3740
G01 X-0.4358 Y99.5001
G01 X-0.2140 Y99.6050
G01 X0.0170 Y99.6877
G01 X0.2550 Y99.7473
G01 X0.4976 Y99.7833
G01 X0.7427 Y99.7953
G01 X85.6900 Y99.7953
G01 X85.9350 Y99.7833
G01 X86.1777 Y99.7473
G01 X86.4157 Y99.6877
G01 X86.6467 Y99.6050
G01 X86.8685 Y99.5001
G01 X87.0789 Y99.3740
G01 X87.2760 Y99.2278
G01 X87.4578 Y99.0631
G01 X87.6225 Y98.8813
G01 X87.7687 Y98.6842
G01 X87.8948 Y98.4738
G01 X87.9997 Y98.2520
G01 X88.0824 Y98.0210
G01 X88.1420 Y97.7830
G01 X88.1780 Y97.5404
G01 X88.1900 Y97.2953
G01 X88.1900 Y0.5207
G01 X88.1780 Y0.2756
G01 X88.1420 Y0.0330
G01 X88.0824 Y-0.2050
G01 X87.9997 Y-0.4360
G01 X87.8948 Y-0.6578
G01 X87.7687 Y-0.8682
G01 X87.6225 Y-1.0653
G01 X87.4578 Y-1.2471
G01 X87.2760 Y-1.4118
G01 X87.0789 Y-1.5580
G01 X86.8685 Y-1.6841
G01 X86.6467 Y-1.7890
G01 X86.4157 Y-1.8717
G01 X86.1777 Y-1.9313
G01 X85.9350 Y-1.9673
G01 X85.6900 Y-1.9793
G00 X85.6900 Y-1.9793
G01 F60.00
G01 Z-0.4000
G01 F60.00
G01 X85.9350 Y-1.9673
G01 X86.1777 Y-1.9313
G01 X86.4157 Y-1.8717
G01 X86.6467 Y-1.7890
G01 X86.8685 Y-1.6841
G01 X87.0789 Y-1.5580
G01 X87.2760 Y-1.4118
G01 X87.4578 Y-1.2471
G01 X87.6225 Y-1.0653
G01 X87.7687 Y-0.8682
G01 X87.8948 Y-0.6578
G01 X87.9997 Y-0.4360
G01 X88.0824 Y-0.2050
G01 X88.1420 Y0.0330
G01 X88.1780 Y0.2756
G01 X88.1900 Y0.5207
G01 X88.1900 Y97.2953
G01 X88.1780 Y97.5404
G01 X88.1420 Y97.7830
G01 X88.0824 Y98.0210
G01 X87.9997 Y98.2520
G01 X87.8948 Y98.4738
G01 X87.7687 Y98.6842
G01 X87.6225 Y98.8813
G01 X87.4578 Y99.0631
G01 X87.2760 Y99.2278
G01 X87.0789 Y99.3740
G01 X86.8685 Y99.5001
G01 X86.6467 Y99.6050
G01 X86.4157 Y99.6877
G01 X86.1777 Y99.7473
G01 X85.9350 Y99.7833
G01 X85.6900 Y99.7953
G01 X0.7427 Y99.7953
G01 X0.4976 Y99.7833
G01 X0.2550 Y99.7473
G01 X0.0170 Y99.6877
G01 X-0.2140 Y99.6050
G01 X-0.4358 Y99.5001
G01 X-0.6462 Y99.3740
G01 X-0.8433 Y99.2278
G01 X-1.0251 Y99.0631
G01 X-1.1898 Y98.8813
G01 X-1.3360 Y98.6842
G01 X-1.4621 Y98.4738
G01 X-1.5670 Y98.2520
G01 X-1.6497 Y98.0210
G01 X-1.7093 Y97.7830
G01 X-1.7453 Y97.5404
G01 X-1.7573 Y97.2953
G01 X-1.7573 Y0.5207
G01 X-1.7453 Y0.2756
G01 X-1.7093 Y0.0330
G01 X-1.6497 Y-0.2050
G01 X-1.5670 Y-0.4360
G01 X-1.4621 Y-0.6578
G01 X-1.3360 Y-0.8682
G01 X-1.1898 Y-1.0653
G01 X-1.0251 Y-1.2471
G01 X-0.8433 Y-1.4118
G01 X-0.6462 Y-1.5580
G01 X-0.4358 Y-1.6841
G01 X-0.2140 Y-1.7890
G01 X0.0170 Y-1.8717
G01 X0.2550 Y-1.9313
G01 X0.4976 Y-1.9673
G01 X0.7427 Y-1.9793
G01 X85.6900 Y-1.9793
G00 X85.6900 Y-1.9793
G01 F60.00
G01 Z-0.6000
G01 F60.00
G01 X0.7427 Y-1.9793
G01 X0.4976 Y-1.9673
G01 X0.2550 Y-1.9313
G01 X0.0170 Y-1.8717
G01 X-0.2140 Y-1.7890
G01 X-0.4358 Y-1.6841
G01 X-0.6462 Y-1.5580
G01 X-0.8433 Y-1.4118
G01 X-1.0251 Y-1.2471
G01 X-1.1898 Y-1.0653
G01 X-1.3360 Y-0.8682
G01 X-1.4621 Y-0.6578
G01 X-1.5670 Y-0.4360
G01 X-1.6497 Y-0.2050
G01 X-1.7093 Y0.0330
G01 X-1.7453 Y0.2756
G01 X-1.7573 Y0.5207
G01 X-1.7573 Y97.2953
G01 X-1.7453 Y97.5404
G01 X-1.7093 Y97.7830
G01 X-1.6497 Y98.0210
G01 X-1.5670 Y98.2520
G01 X-1.4621 Y98.4738
G01 X-1.3360 Y98.6842
G01 X-1.1898 Y98.8813
G01 X-1.0251 Y99.0631
G01 X-0.8433 Y99.2278
G01 X-0.6462 Y99.3740
G01 X-0.4358 Y99.5001
G01 X-0.2140 Y99.6050
G01 X0.0170 Y99.6877
G01 X0.2550 Y99.7473
G01 X0.4976 Y99.7833
G01 X0.7427 Y99.7953
G01 X85.6900 Y99.7953
G01 X85.9350 Y99.7833
G01 X86.1777 Y99.7473
G01 X86.4157 Y99.6877
G01 X86.6467 Y99.6050
G01 X86.8685 Y99.5001
G01 X87.0789 Y99.3740
G01 X87.2760 Y99.2278
G01 X87.4578 Y99.0631
G01 X87.6225 Y98.8813
G01 X87.7687 Y98.6842
G01 X87.8948 Y98.4738
G01 X87.9997 Y98.2520
G01 X88.0824 Y98.0210
G01 X88.1420 Y97.7830
G01 X88.1780 Y97.5404
G01 X88.1900 Y97.2953
G01 X88.1900 Y0.5207
G01 X88.1780 Y0.2756
G01 X88.1420 Y0.0330
G01 X88.0824 Y-0.2050
G01 X87.9997 Y-0.4360
G01 X87.8948 Y-0.6578
G01 X87.7687 Y-0.8682
G01 X87.6225 Y-1.0653
G01 X87.4578 Y-1.2471
G01 X87.2760 Y-1.4118
G01 X87.0789 Y-1.5580
G01 X86.8685 Y-1.6841
G01 X86.6467 Y-1.7890
G01 X86.4157 Y-1.8717
G01 X86.1777 Y-1.9313
G01 X85.9350 Y-1.9673
G01 X85.6900 Y-1.9793
G00 X85.6900 Y-1.9793
G01 F60.00
G01 Z-0.8000
G01 F60.00
G01 X85.9350 Y-1.9673
G01 X86.1777 Y-1.9313
G01 X86.4157 Y-1.8717
G01 X86.6467 Y-1.7890
G01 X86.8685 Y-1.6841
G01 X87.0789 Y-1.5580
G01 X87.2760 Y-1.4118
G01 X87.4578 Y-1.2471
G01 X87.6225 Y-1.0653
G01 X87.7687 Y-0.8682
G01 X87.8948 Y-0.6578
G01 X87.9997 Y-0.4360
G01 X88.0824 Y-0.2050
G01 X88.1420 Y0.0330
G01 X88.1780 Y0.2756
G01 X88.1900 Y0.5207
G01 X88.1900 Y97.2953
G01 X88.1780 Y97.5404
G01 X88.1420 Y97.7830
G01 X88.0824 Y98.0210
G01 X87.9997 Y98.2520
G01 X87.8948 Y98.4738
G01 X87.7687 Y98.6842
G01 X87.6225 Y98.8813
G01 X87.4578 Y99.0631
G01 X87.2760 Y99.2278
G01 X87.0789 Y99.3740
G01 X86.8685 Y99.5001
G01 X86.6467 Y99.6050
G01 X86.4157 Y99.6877
G01 X86.1777 Y99.7473
G01 X85.9350 Y99.7833
G01 X85.6900 Y99.7953
G01 X0.7427 Y99.7953
G01 X0.4976 Y99.7833
G01 X0.2550 Y99.7473
G01 X0.0170 Y99.6877
G01 X-0.2140 Y99.6050
G01 X-0.4358 Y99.5001
G01 X-0.6462 Y99.3740
G01 X-0.8433 Y99.2278
G01 X-1.0251 Y99.0631
G01 X-1.1898 Y98.8813
G01 X-1.3360 Y98.6842
G01 X-1.4621 Y98.4738
G01 X-1.5670 Y98.2520
G01 X-1.6497 Y98.0210
G01 X-1.7093 Y97.7830
G01 X-1.7453 Y97.5404
G01 X-1.7573 Y97.2953
G01 X-1.7573 Y0.5207
G01 X-1.7453 Y0.2756
G01 X-1.7093 Y0.0330
G01 X-1.6497 Y-0.2050
G01 X-1.5670 Y-0.4360
G01 X-1.4621 Y-0.6578
G01 X-1.3360 Y-0.8682
G01 X-1.1898 Y-1.0653
G01 X-1.0251 Y-1.2471
G01 X-0.8433 Y-1.4118
G01 X-0.6462 Y-1.5580
G01 X-0.4358 Y-1.6841
G01 X-0.2140 Y-1.7890
G01 X0.0170 Y-1.8717
G01 X0.2550 Y-1.9313
G01 X0.4976 Y-1.9673
G01 X0.7427 Y-1.9793
G01 X85.6900 Y-1.9793
G00 X85.6900 Y-1.9793
G01 F60.00
G01 Z-1.0000
G01 F60.00
G01 X0.7427 Y-1.9793
G01 X0.4976 Y-1.9673
G01 X0.2550 Y-1.9313
G01 X0.0170 Y-1.8717
G01 X-0.2140 Y-1.7890
G01 X-0.4358 Y-1.6841
G01 X-0.6462 Y-1.5580
G01 X-0.8433 Y-1.4118
G01 X-1.0251 Y-1.2471
G01 X-1.1898 Y-1.0653
G01 X-1.3360 Y-0.8682
G01 X-1.4621 Y-0.6578
G01 X-1.5670 Y-0.4360
G01 X-1.6497 Y-0.2050
G01 X-1.7093 Y0.0330
G01 X-1.7453 Y0.2756
G01 X-1.7573 Y0.5207
G01 X-1.7573 Y97.2953
G01 X-1.7453 Y97.5404
G01 X-1.7093 Y97.7830
G01 X-1.6497 Y98.0210
G01 X-1.5670 Y98.2520
G01 X-1.4621 Y98.4738
G01 X-1.3360 Y98.6842
G01 X-1.1898 Y98.8813
G01 X-1.0251 Y99.0631
G01 X-0.8433 Y99.2278
G01 X-0.6462 Y99.3740
G01 X-0.4358 Y99.5001
G01 X-0.2140 Y99.6050
G01 X0.0170 Y99.6877
G01 X0.2550 Y99.7473
G01 X0.4976 Y99.7833
G01 X0.7427 Y99.7953
G01 X85.6900 Y99.7953
G01 X85.9350 Y99.7833
G01 X86.1777 Y99.7473
G01 X86.4157 Y99.6877
G01 X86.6467 Y99.6050
G01 X86.8685 Y99.5001
G01 X87.0789 Y99.3740
G01 X87.2760 Y99.2278
G01 X87.4578 Y99.0631
G01 X87.6225 Y98.8813
G01 X87.7687 Y98.6842
G01 X87.8948 Y98.4738
G01 X87.9997 Y98.2520
G01 X88.0824 Y98.0210
G01 X88.1420 Y97.7830
G01 X88.1780 Y97.5404
G01 X88.1900 Y97.2953
G01 X88.1900 Y0.5207
G01 X88.1780 Y0.2756
G01 X88.1420 Y0.0330
G01 X88.0824 Y-0.2050
G01 X87.9997 Y-0.4360
G01 X87.8948 Y-0.6578
G01 X87.7687 Y-0.8682
G01 X87.6225 Y-1.0653
G01 X87.4578 Y-1.2471
G01 X87.2760 Y-1.4118
G01 X87.0789 Y-1.5580
G01 X86.8685 Y-1.6841
G01 X86.6467 Y-1.7890
G01 X86.4157 Y-1.8717
G01 X86.1777 Y-1.9313
G01 X85.9350 Y-1.9673
G01 X85.6900 Y-1.9793
G00 X85.6900 Y-1.9793
G01 F60.00
G01 Z-1.2000
G01 F60.00
G01 X85.9350 Y-1.9673
G01 X86.1777 Y-1.9313
G01 X86.4157 Y-1.8717
G01 X86.6467 Y-1.7890
G01 X86.8685 Y-1.6841
G01 X87.0789 Y-1.5580
G01 X87.2760 Y-1.4118
G01 X87.4578 Y-1.2471
G01 X87.6225 Y-1.0653
G01 X87.7687 Y-0.8682
G01 X87.8948 Y-0.6578
G01 X87.9997 Y-0.4360
G01 X88.0824 Y-0.2050
G01 X88.1420 Y0.0330
G01 X88.1780 Y0.2756
G01 X88.1900 Y0.5207
G01 X88.1900 Y97.2953
G01 X88.1780 Y97.5404
G01 X88.1420 Y97.7830
G01 X88.0824 Y98.0210
G01 X87.9997 Y98.2520
G01 X87.8948 Y98.4738
G01 X87.7687 Y98.6842
G01 X87.6225 Y98.8813
G01 X87.4578 Y99.0631
G01 X87.2760 Y99.2278
G01 X87.0789 Y99.3740
G01 X86.8685 Y99.5001
G01 X86.6467 Y99.6050
G01 X86.4157 Y99.6877
G01 X86.1777 Y99.7473
G01 X85.9350 Y99.7833
G01 X85.6900 Y99.7953
G01 X0.7427 Y99.7953
G01 X0.4976 Y99.7833
G01 X0.2550 Y99.7473
G01 X0.0170 Y99.6877
G01 X-0.2140 Y99.6050
G01 X-0.4358 Y99.5001
G01 X-0.6462 Y99.3740
G01 X-0.8433 Y99.2278
G01 X-1.0251 Y99.0631
G01 X-1.1898 Y98.8813
G01 X-1.3360 Y98.6842
G01 X-1.4621 Y98.4738
G01 X-1.5670 Y98.2520
G01 X-1.6497 Y98.0210
G01 X-1.7093 Y97.7830
G01 X-1.7453 Y97.5404
G01 X-1.7573 Y97.2953
G01 X-1.7573 Y0.5207
G01 X-1.7453 Y0.2756
G01 X-1.7093 Y0.0330
G01 X-1.6497 Y-0.2050
G01 X-1.5670 Y-0.4360
G01 X-1.4621 Y-0.6578
G01 X-1.3360 Y-0.8682
G01 X-1.1898 Y-1.0653
G01 X-1.0251 Y-1.2471
G01 X-0.8433 Y-1.4118
G01 X-0.6462 Y-1.5580
G01 X-0.4358 Y-1.6841
G01 X-0.2140 Y-1.7890
G01 X0.0170 Y-1.8717
G01 X0.2550 Y-1.9313
G01 X0.4976 Y-1.9673
G01 X0.7427 Y-1.9793
G01 X85.6900 Y-1.9793
G00 X85.6900 Y-1.9793
G01 F60.00
G01 Z-1.4000
G01 F60.00
G01 X0.7427 Y-1.9793
G01 X0.4976 Y-1.9673
G01 X0.2550 Y-1.9313
G01 X0.0170 Y-1.8717
G01 X-0.2140 Y-1.7890
G01 X-0.4358 Y-1.6841
G01 X-0.6462 Y-1.5580
G01 X-0.8433 Y-1.4118
G01 X-1.0251 Y-1.2471
G01 X-1.1898 Y-1.0653
G01 X-1.3360 Y-0.8682
G01 X-1.4621 Y-0.6578
G01 X-1.5670 Y-0.4360
G01 X-1.6497 Y-0.2050
G01 X-1.7093 Y0.0330
G01 X-1.7453 Y0.2756
G01 X-1.7573 Y0.5207
G01 X-1.7573 Y97.2953
G01 X-1.7453 Y97.5404
G01 X-1.7093 Y97.7830
G01 X-1.6497 Y98.0210
G01 X-1.5670 Y98.2520
G01 X-1.4621 Y98.4738
G01 X-1.3360 Y98.6842
G01 X-1.1898 Y98.8813
G01 X-1.0251 Y99.0631
G01 X-0.8433 Y99.2278
G01 X-0.6462 Y99.3740
G01 X-0.4358 Y99.5001
G01 X-0.2140 Y99.6050
G01 X0.0170 Y99.6877
G01 X0.2550 Y99.7473
G01 X0.4976 Y99.7833
G01 X0.7427 Y99.7953
G01 X85.6900 Y99.7953
G01 X85.9350 Y99.7833
G01 X86.1777 Y99.7473
G01 X86.4157 Y99.6877
G01 X86.6467 Y99.6050
G01 X86.8685 Y99.5001
G01 X87.0789 Y99.3740
G01 X87.2760 Y99.2278
G01 X87.4578 Y99.0631
G01 X87.6225 Y98.8813
G01 X87.7687 Y98.6842
G01 X87.8948 Y98.4738
G01 X87.9997 Y98.2520
G01 X88.0824 Y98.0210
G01 X88.1420 Y97.7830
G01 X88.1780 Y97.5404
G01 X88.1900 Y97.2953
G01 X88.1900 Y0.5207
G01 X88.1780 Y0.2756
G01 X88.1420 Y0.0330
G01 X88.0824 Y-0.2050
G01 X87.9997 Y-0.4360
G01 X87.8948 Y-0.6578
G01 X87.7687 Y-0.8682
G01 X87.6225 Y-1.0653
G01 X87.4578 Y-1.2471
G01 X87.2760 Y-1.4118
G01 X87.0789 Y-1.5580
G01 X86.8685 Y-1.6841
G01 X86.6467 Y-1.7890
G01 X86.4157 Y-1.8717
G01 X86.1777 Y-1.9313
G01 X85.9350 Y-1.9673
G01 X85.6900 Y-1.9793
G00 X85.6900 Y-1.9793
G01 F60.00
G01 Z-1.6000
G01 F60.00
G01 X85.9350 Y-1.9673
G01 X86.1777 Y-1.9313
G01 X86.4157 Y-1.8717
G01 X86.6467 Y-1.7890
G01 X86.8685 Y-1.6841
G01 X87.0789 Y-1.5580
G01 X87.2760 Y-1.4118
G01 X87.4578 Y-1.2471
G01 X87.6225 Y-1.0653
G01 X87.7687 Y-0.8682
G01 X87.8948 Y-0.6578
G01 X87.9997 Y-0.4360
G01 X88.0824 Y-0.2050
G01 X88.1420 Y0.0330
G01 X88.1780 Y0.2756
G01 X88.1900 Y0.5207
G01 X88.1900 Y97.2953
G01 X88.1780 Y97.5404
G01 X88.1420 Y97.7830
G01 X88.0824 Y98.0210
G01 X87.9997 Y98.2520
G01 X87.8948 Y98.4738
G01 X87.7687 Y98.6842
G01 X87.6225 Y98.8813
G01 X87.4578 Y99.0631
G01 X87.2760 Y99.2278
G01 X87.0789 Y99.3740
G01 X86.8685 Y99.5001
G01 X86.6467 Y99.6050
G01 X86.4157 Y99.6877
G01 X86.1777 Y99.7473
G01 X85.9350 Y99.7833
G01 X85.6900 Y99.7953
G01 X0.7427 Y99.7953
G01 X0.4976 Y99.7833
G01 X0.2550 Y99.7473
G01 X0.0170 Y99.6877
G01 X-0.2140 Y99.6050
G01 X-0.4358 Y99.5001
G01 X-0.6462 Y99.3740
G01 X-0.8433 Y99.2278
G01 X-1.0251 Y99.0631
G01 X-1.1898 Y98.8813
G01 X-1.3360 Y98.6842
G01 X-1.4621 Y98.4738
G01 X-1.5670 Y98.2520
G01 X-1.6497 Y98.0210
G01 X-1.7093 Y97.7830
G01 X-1.7453 Y97.5404
G01 X-1.7573 Y97.2953
G01 X-1.7573 Y0.5207
G01 X-1.7453 Y0.2756
G01 X-1.7093 Y0.0330
G01 X-1.6497 Y-0.2050
G01 X-1.5670 Y-0.4360
G01 X-1.4621 Y-0.6578
G01 X-1.3360 Y-0.8682
G01 X-1.1898 Y-1.0653
G01 X-1.0251 Y-1.2471
G01 X-0.8433 Y-1.4118
G01 X-0.6462 Y-1.5580
G01 X-0.4358 Y-1.6841
G01 X-0.2140 Y-1.7890
G01 X0.0170 Y-1.8717
G01 X0.2550 Y-1.9313
G01 X0.4976 Y-1.9673
G01 X0.7427 Y-1.9793
G01 X85.6900 Y-1.9793
G00 Z2.0000
M05
G00 Z2.0000
G00 Z15.00

