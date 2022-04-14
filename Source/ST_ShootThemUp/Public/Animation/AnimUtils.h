#pragma once

class AnimUtils
{
public:

    template <typename T> static T* FindNotifyByClass(UAnimSequenceBase* Animation)
    {
        if (Animation)
        {
            const auto NotifyEvent = Animation->Notifies;

            for (auto elem : NotifyEvent)
            {
                auto AnimNotify = Cast<T>(elem.Notify);
                if (AnimNotify)
                {
                    return AnimNotify;
                }
            }
        }
        return nullptr;
    }
};