#ifndef MINI_MAP_H
#define MINI_MAP_H

//显示小地图;当前角色x轴位置
void	MMP_ShowMap(int x,int y);

//显示角色当前所处房间周围8个格子中尚未显示的房间
void	MMP_ShowNextRoom(int level);

#endif // !MINI_MAP_H
