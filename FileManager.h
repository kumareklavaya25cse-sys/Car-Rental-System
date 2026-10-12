#ifndef FILEMANAGER_H
#define FILEMANAGER_H

class RentalSystem;

class FileManager {
public:
    // Save all system records to files
    void save(const RentalSystem& system);

    // Load saved records into the system
    void load(RentalSystem& system);
};

#endif