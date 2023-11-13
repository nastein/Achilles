add_library(AchillesHepMC3 SHARED HepMC3EventWriter.cc)
# target_include_directories(AchillesHepMC3 PUBLIC ${HEPMC3_INCLUDE_DIR})
target_link_libraries(AchillesHepMC3 PRIVATE project_options
                             PUBLIC HepMC3 physics fmt::fmt spdlog::spdlog yaml::cpp)
