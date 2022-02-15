Folders in the archive:
- cavitatingNoGasFoam: OpenFOAM code for simulations of cavitating flows without degassing;
- cavitationAndGasReleaseFoam: OpenFOAM code for simulations of cavitating flows with included degassing (gas release) model;
- Test_cases: 4 folders with computational setup files (2 geometries, both with and without degassing) and papers on these experiments


Instructions for compiling the code and using it for CFD simulations in OpenFOAM:


1. To compile the code and create an executable OpenFOAM solver:

- Open the terminal and go to the directory of the code (normally looks like: ../OpenFOAM/../solvers/cavitationAndGasReleaseFoam);

- Enter the command "wmake", and in case of no problems OpenFOAM will build an application (for example, cavitationAndGasReleaseFoam);

- If occasionally some OpenFOAM libraries are missing (may happen) and an error occurs, try "wmake libso" and then again "wmake";


2. To work with the test cases:

- Copy the folder with the test case you would like to try (for example, "Throttle_experiment_with_degassing") into some directory;

- Open the terminal and go to this directory (normally looks like: ../OpenFOAM/../run/Throttle_experiment_with_degassing, but can be saved anywhere);

- Run the command "blockMesh" to construct the computational mesh with the parameters defined in the "blockMeshDict" file ("system" folder);
	- It is also possible to use meshes constructed in other programs and convert them into OpenFOAM format, but in these tests we don't have it.
	- To change something in the mesh, just edit the "blockMeshDict" file. In the current version a detailed 3D mesh suitable for LES is constructed.
	
- Edit the "controlDict" file ("system" folder) to define the basic settings of the simulation (simulation time, time step, binary/ascii data format , etc.)

- To check or change something else (for example, boundary conditions, physical parameters of the fluids, numerical schemes to compute the fluxes, etc.):
	- Boundary conditions are defined and can be changed for each field (pressure, velocity, etc.) in the corresponding file in the "0" folder";
	- Initial fields (zero time moment) can be specified as uniform as well as non-uniform (use the "setFieldsDict" file in the "system" folder);
	- Physical parameters are defined and can be changed in the "constant" folder in the files "thermodynamicProperties" and "transportProperties";
	- Numerical scheme used by the finite volume method can be defined for each conservation equation separately in the "fvSchemes" file ("system" folder).
	- Comment: in the current version of these files all the settings are done based on the information available in the papers describing the experiments.
	
- After everything is defined, run the command "setFields" (if you want to change something in the initial fields) and then run the solver itself.
(just in case, "run the solver" means run the command named after the name of the solver, for example "cavitationAndGasReleaseFoam")


3. Post-processing of the results: after the simulation is finished, run the command "paraFoam" to visualize the results in ParaView (if ParaView is installed).
	- One more comment: the folder "postProcessing" created in the simulation directory contains the output of the flow parameters in monitoring points;
	- The coordinates of the monitoring points and the values to monitor are defined and can be changed in the "contolDict" file in the "probes" subsection.
