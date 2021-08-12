file1='E:\Research\data\Segy\CMP_INL2000_stk_org_gain.SEGY'
[seismic,text_header1,binary_header1]=read_segy_file(file1);
s_cplot(seismic,{'time_lines',[]})