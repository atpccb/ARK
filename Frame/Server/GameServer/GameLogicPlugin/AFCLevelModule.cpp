/*
* This source file is part of ArkGameFrame
* For the latest info, see https://github.com/ArkGame
*
* Copyright (c) 2013-2017 ArkGame authors.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
*/

#include "AFCLevelModule.h"

bool AFCLevelModule::Init()
{
    return true;
}


bool AFCLevelModule::Shut()
{
    return true;
}

void AFCLevelModule::Update()
{

}

bool AFCLevelModule::AfterInit()
{
    m_pKernelModule = pPluginManager->FindModule<AFIKernelModule>();
    m_pLogModule = pPluginManager->FindModule<AFILogModule>();
    m_pPropertyConfigModule = pPluginManager->FindModule<AFIPropertyConfigModule>();
    m_pElementModule = pPluginManager->FindModule<AFIElementModule>();

    return true;
}

int AFCLevelModule::AddExp(const AFGUID& self, const int nExp)
{
    int eJobType = m_pKernelModule->GetNodeInt(self, ARK::Player::Job());
    int nCurExp = m_pKernelModule->GetNodeInt(self, ARK::Player::EXP());
    int nLevel = m_pKernelModule->GetNodeInt(self, ARK::Player::Level());
    int nMaxExp = m_pPropertyConfigModule->CalculateBaseValue(eJobType, nLevel, ARK::Player::MAXEXP());

    nCurExp += nExp;

    int nRemainExp = nCurExp - nMaxExp;
    while (nRemainExp >= 0)
    {
        //����
        nLevel++;
        //��ֹԽ��BUG
        m_pKernelModule->SetNodeInt(self, ARK::Player::Level(), nLevel);

        nCurExp = nRemainExp;

        nMaxExp = m_pPropertyConfigModule->CalculateBaseValue(eJobType, nLevel, ARK::Player::MAXEXP());
        if (nMaxExp <= 0)
        {
            break;
        }

        nRemainExp -= nMaxExp;
    }

    m_pKernelModule->SetNodeInt(self, ARK::Player::EXP(), nCurExp);

    return 0;
}

