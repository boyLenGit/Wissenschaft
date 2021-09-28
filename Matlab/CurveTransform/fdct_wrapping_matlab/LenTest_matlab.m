clc
% x1=[1,2,3,4,5,6,2,1,4,5,6,2];
% x=[0.3, 1, 3, 0.4, 5, 0.3];
% x((x > 0) & (x < 1))=[100,200,300,400,500,600]

x3 = [1 2 3 4 5 6 7;
    11 2 3 4 5 6 7;
    1 2 3 4 5 6 7;
    1 2 3 4 5 6 7;
    1 2 3 4 5 6 7;
    1 2 3 4 5 6 7;
    1 2 3 4 5 6 7];
x4 = [1.1,2.1,3.1,4.1,5.1,6.1,7.1,8.1,9.1];
x5 = [3,2,1,1,1,4];
x5(end)

List_Reward = [];  % 存储所有Reward
List_T = [];  % 存储所有时间
Cnt = 1;  % for循环计数器
for T = 0:0.5:20
    ES = 1;
    Reward = ES * T^2;   % 求Reward的表达式
    List_Reward(Cnt) = Reward;
    List_T(Cnt) = T;
    Cnt = Cnt + 1; % for循环计数器累加
end

[max_value, max_value_position] = max(List_Reward);  % 求最大值与最大值所在位置
disp('最大值与当前时间为：')
max_value
List_T(max_value_position)