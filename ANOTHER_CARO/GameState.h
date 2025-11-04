#pragma once

// Định nghĩa các "trang" (trạng thái) mà game của bạn có
enum class GameState {
    MainMenu,
    NewGame, // Đây là trang "New Game"
    // Settings, // (Sẽ thêm sau)
    AboutUs,  // (Sẽ thêm sau)
    Tutorials,
    TwoPlayer,
    ThreePlayer,
    Playing,
    Exiting
};