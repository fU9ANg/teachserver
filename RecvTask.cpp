#include "RecvTask.h"
RecvTask::RecvTask() {
}

RecvTask::~RecvTask() {
}

int RecvTask::work() {
    while(true){
        Buf* p = NULL;
        if (0 != SINGLE->recvqueue.dequeue(p, 3)) {
            continue;
        }
        printf("get msg %s\n", (char*)((char*)p->ptr() + sizeof(int)));


        switch(((MSG_HEAD*)p->ptr())->cType) 
        {
            case CT_Login:           // 登录 (所有端)
                break;
            case CT_LoginReuslt:     // 登录结果 (所有端)
                break;
            case CT_GetCourseDB:     // 获得数据库中的课程信息 (教师端)
                break;
            case CT_SetCourseList:   // 设置开启的课程列表 (教师端)
                break;
            case CT_GetCourseList:   // 获得课程列表 (教师端和所有学生端)
                break;
            case CT_GetCourseListItem: // 获得课程列表的子项 (教师端)
                break;
            case CT_Logout:           // 登出 (所有端)
                break;
            case CT_LogoutReuslt:     // 登出结果 (所有端)
                break;
            case CT_GetClassRoomDB:    // 获得教室班级数据库信息 (教师端)
                break;
            case CT_GetGradeDB:    // 获得教室年级数据库信息 (教师端)
                break;
            case CT_LoginClassRoom:   // 进入教室 (所有学生端)
                break;
            case CT_LogoutClassRoom:  // 退出教室 (教师端和所有学生端)
                break;
            case CT_GetStudentInfo:   // 获得学生列表 (所有端)
                break;
            case CT_GetAllStudentInfo:// 获得所有学生列表 (所有端)
                break;
            case CT_LeaveEarly:       // 早退 (教师端)
                break;
            case CT_ConfirmLeaveEarly:// 早退确认 (学生端)
                break;
            case CT_GetTeacherInfo:   // 获得教师信息 (所有学生端和教师端)
                break;
            case CT_ShowSpriteChuanChuang: // 串场动画 (教师端)
                break;
            case ST_GoSpriteChuanChuang:      // 显示串场动画 (白板端)
                break;
            case CT_ShowSpriteKongChang:   // 控场动画 (教师端)
                break;
            case ST_GoSpriteKongChang:        // 控场动画显示 (白板端)
                break;
            case CT_KongChangLevel:           // 控场级别 (教师端)
                break;
            case ST_KongChangLevel:           // 显示控场动画级别 (白板端)
                break;
            case CT_NuanShenCao_GameStart:     // 暖身操环节开始 (教师端)
                break;
            case ST_NuanShenCao_GameStart:        // 暖身操开始播放 (白板端)
                break;
            case CT_NuanShenCao_Play:             //  暖身操播放 (教师端)
                break;
            case ST_NuanShenCao_Play:             //  暖身操播放 (白板端)
                break;
            case CT_NuanShenCao_Pause:            // 暖身操暂停 (教师端)
                break;
            case ST_NuanShenCao_Pause:            // 暖身操暂停 (白板端)
                break;
            case CT_NuanShenCao_Stop:             // 暖身操停止 (教师端)
                break;
            case ST_NuanShenCao_Stop:             // 暖身操停止 (白板端)
                break;
            case CT_NuanShenCao_GameEnd:          // 暖身操环节结束 (教师端)
                break;
            case ST_NuanShenCao_GameEnd:          // 暖身操结束播放 (白板端)
                break;
            case CT_DongHuaPian_GameStart:     // 动画片环节开始 (教师端)
                break;
            case ST_DongHuaPian_GameStart:        // 动画片开始 (白板端)
                break;
            case CT_DongHuaPian_Play:             //  动画片播放 (教师端)
                break;
            case ST_DongHuaPian_Play:             //  动画片播放 (白板端)
                break;
            case CT_DongHuaPian_Pause:            //  动画片暂停 (教师端)
                break;
            case ST_DongHuaPian_Pause:            //  动画片暂停 (白板端)
                break;
            case CT_DongHuaPian_Stop:            //  动画片停止 (教师端)
                break;
            case ST_DongHuaPian_Stop:            //  动画片停止 (白板端)
                break;
            case CT_DongHuaPian_GameEnd:          // 动画片环节结束 (教师端)
                break;
            case ST_DongHuaPian_GameEnd:          // 动画片结束播放 (白板端)
                break;
            case CT_ZaoFangZi_CaiHongXiaoWu:   // 彩虹小屋文字 (教师端)
                break;
            case ST_ZaoFangZi_CaiHongXiaoWu:  // 显示彩虹小屋文字 (白板端)
                break;
            case CT_ZaoFangZi_CaiHongGu:      // 彩虹谷文字 (教师端)
                break;
            case ST_ZaoFangZi_CaiHongGu:      // 显示彩虹谷背景 (白板端)
                break;
            case CT_ZaoFangZi_XiaoGuaiWu:     // 小怪物文字 (教师端)
                break;
            case ST_ZaoFangZi_XiaoGuaiWu:     // 显示小怪物图片 (白板端)
                break;
            case CT_ZaoFangZi_MuBu:           // 幕布文字 (教师端)
                break;
            case ST_ZaoFangZi_MuBu:           // 显示幕布 (白板端)
                break;
            case CT_ZaoFangZi_Operator:       // 操作演示 (教师端)
                break;
            case ST_ZaoFangZi_Operator:       // 响应教师的操作演示 (白板端)
                break;
            case CT_ZaoFangZi_OnlyOne:        // 单人模式 (教师端)
                break;
            case ST_ZaoFangZi_OnlyOne:        // 响应所有学生的单人模式操作情况 (白板端)
                break;
            case CT_ZaoFangZi_OnlyGroup:      // 分组模式 (教师端)
                break;
            case ST_ZaoFangZi_OnlyGroup:      // 响应分组模式操作情况 (白板端)
                break;
            case CT_ZaoFangZi_SetStuGroup:    // 设置学生组信息 (教师端)
                break;
            case CT_ZaoFangZi_GetStuGroup:    // 获得学生组信息 (所有客户端)
                break;
            case CT_ZaoFangZi_GameStart:      // 造房子游戏开始 (教师端)
                break;
            case ST_ZaoFangZi_GameStart:      // 同步所有(学生端和白板端)
                break;
            case CT_ZaoFangZi_Material:       // 获得素材 (所有学生端) *
                break;
            case CT_ZaoFangZi_UpdatePos:      // 学生添加/移动/删除素材 (所有学生端)
                break;
            case ST_ZaoFangZi_UpdatePos:      // 同步造房子进度 (白板端)
                break;
            case CT_ZaoFangZi_Email:          // 启动邮件 (教师端)
                break;
            case ST_ZaoFangZi_Email:          // 显示邮件信息 (白板端)
                break;
            case CT_ZaoFangZi_JiHe:           // 激活 (教师端)
                break;
            case ST_ZaoFangZi_JiHe:           // 激活场景 (白板端)
                break;
            case CT_ZaoFangZi_DengChang:      // 角色登场 (教师端)
                break;
            case ST_ZaoFangZi_DengChang:      // 角色登场 (白板端)
                break;
            case CT_ZaoFangZi_GaiZhang:       // 盖章 (教师端)
                break;
            case ST_ZaoFangZi_GaiZhang:       // 盖章 (白板端)
                break;
            case CT_ZaoFangZi_GameEnd:        // 发起造房子游戏结束 (教师端)
                break;
            case ST_ZaoFangZi_GameEnd:        // 同步所有(学生端和白板端)
                break;
            case CT_ZaoFangZi_Save:           // 发送创建好的房子到服务器 (所有学生端) *
                break;
            case CT_ZaoFangZi_ConfirmGaiZhang:// 盖章确认 (教师端)
                break;
            case CT_PingTu_GameStart:       // 点击拼图开始 (教师端)
                break;
            case ST_PingTu_GameStart:         // 发送拼图游戏开始信息 (学生端和白板端)
                break;
            case CT_PingTu_GetPic:            // 发送某一拼图原图 (学生端和白板端) *
                break;
            case CT_PingTu_IconStatus:        // 获得拼图是否正确的状态 (学生端)
                break;
            case ST_PingTu_IconStatus:        // 发送拼图是否正确的状态 (白板端)
                break;
            case CT_PingTu_SetScore:          // 设置拼图的结果 (学生端) *
                break;
            case CT_PingTu_MovePic:           // 拼图区中移动某一拼图块 (客户端)
                break;
            case ST_PingTu_MovePic:           // 拼图区中移动某一拼图块 (白板端)
                break;
            case CT_PingTu_DeletePic:         // 拼图区中删除某一拼图块 (客户端)
                break;
            case ST_PingTu_DeletePic:         // 拼图区中删除某一拼图块 (白板端)
                break;
            case CT_PingTu_AddPic:            // 拼图区中添加某一拼图块 (客户端)
                break;
            case ST_PingTu_AddPic:            // 拼图区中添加某一拼图块 (白板端)
                break;
            case CT_PingTu_EndGame:           // 结束拼图课程 (教师端)
                break;
            case ST_PingTu_EndGame:           // 结束拼图课程 (白板端和所有学生端)
                break;
        }

        p->reset();
        SINGLE->bufpool.free(p);
    }
    return 0;
}
