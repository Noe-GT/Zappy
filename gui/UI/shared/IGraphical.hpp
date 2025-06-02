/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** IGraphical
*/


#pragma once

namespace zappyGUI {
    class IGraphical {
        public:
            IGraphical();
            ~IGraphical();
            virtual void display() = 0;
            virtual void update() = 0;
            virtual void handleEvents() = 0;
    
        protected:
        private:
    };
};

