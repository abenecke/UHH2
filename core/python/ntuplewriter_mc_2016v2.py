import FWCore.ParameterSet.Config as cms
from UHH2.core.ntuple_generator import generate_process  # use CMSSW type path for CRAB
from UHH2.core.optionsParse import setup_opts, parse_apply_opts


"""NTuple config for 2016 v2 miniaod MC datasets.

You should try and put any centralised changes in generate_process(), not here.
"""


process = generate_process(year="2016v2", useData=False)

# Please do not commit changes to source filenames - used for consistency testing
process.source.fileNames = cms.untracked.vstring([
'/store/mc/RunIISummer16MiniAODv2/QCD_Pt-15to7000_TuneCUETP8M1_Flat_13TeV_pythia8/MINIAODSIM/PUFlat0to70_magnetOn_80X_mcRun2_asymptotic_2016_TrancheIV_v4-v1/90000/102D73A7-5B87-E611-936E-0CC47A1E0472.root'
])

# Do this after setting process.source.fileNames, since we want the ability to override it on the commandline
options = setup_opts()
parse_apply_opts(process, options)

with open('pydump_mc_2016v2.py', 'w') as f:
    f.write(process.dumpPython())
