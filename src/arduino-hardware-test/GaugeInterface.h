#pragma once

class GaugeInterface
{
    public:
        virtual void begin() = 0;
        virtual void update() = 0;
};

