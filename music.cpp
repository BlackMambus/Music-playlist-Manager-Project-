    #include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

class Song {
public:
    std::string title;
    std::string artist;

    Song(std::string t, std::string a) : title(t), artist(a) {}

    void display() const {
        std::cout << "🎶 " << title << " by " << artist << std::endl;
    }
};

class PlaylistManager {
private:
    std::vector<Song> playlist;

public:
    void addSong(const std::string& title, const std::string& artist) {
        playlist.emplace_back(title, artist);
        std::cout << "✅ Added: " << title << " by " << artist << std::endl;
    }

    void viewPlaylist() const {
        if (playlist.empty()) {
            std::cout << "📭 Playlist is empty.\n";
            return;
        }
        std::cout << "\n🎧 Your Playlist:\n";
        for (size_t i = 0; i < playlist.size(); ++i) {
            std::cout << i + 1 << ". ";
            playlist[i].display();
        }
    }

    void removeSong(int index) {
        if (index < 1 || index > playlist.size()) {
            std::cout << "❌ Invalid index.\n";
            return;
        }
        std::cout << "🗑️ Removed: " << playlist[index - 1].title << std::endl;
        playlist.erase(playlist.begin() + index - 1);
    }

    void saveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        for (const auto& song : playlist) {
            file << song.title << "," << song.artist << "\n";
        }
        std::cout << "💾 Playlist saved to " << filename << std::endl;
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        std::string line;
        playlist.clear();
        while (getline(file, line)) {
            size_t comma = line.find(',');
            if (comma != std::string::npos) {
                std::string title = line.substr(0, comma);
                std::string artist = line.substr(comma + 1);
                playlist.emplace_back(title, artist);
            }
        }
        std::cout << "📂 Playlist loaded from " << filename << std::endl;
    }
};
int main() {
    PlaylistManager manager;
    int choice;
    std::string title, artist, filename;
    int index;

    do {
        std::cout << "\n🎵 Playlist Manager\n";
        std::cout << "1. Add Song\n2. View Playlist\n3. Remove Song\n4. Save Playlist\n5. Load Playlist\n0. Exit\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;
        std::cin.ignore(); // Clear newline

        switch (choice) {
            case 1:
                std::cout << "Enter song title: ";
                getline(std::cin, title);
                std::cout << "Enter artist name: ";
                getline(std::cin, artist);
                manager.addSong(title, artist);
                break;
            case 2:
                manager.viewPlaylist();
                break;
            case 3:
                std::cout << "Enter song number to remove: ";
                std::cin >> index;
                manager.removeSong(index);
                break;
            case 4:
                std::cout << "Enter filename to save: ";
                std::cin >> filename;
                manager.saveToFile(filename);
                break;
            case 5:
                std::cout << "Enter filename to load: ";
                std::cin >> filename;
                manager.loadFromFile(filename);
                break;
            case 0:
                std::cout << "👋 Goodbye!\n";
                break;
            default:
                std::cout << "❗ Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}



