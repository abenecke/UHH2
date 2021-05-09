import FWCore.ParameterSet.Config as cms
from UHH2.core.ntuple_generator import generate_process  # use CMSSW type path for CRAB
from UHH2.core.optionsParse import setup_opts, parse_apply_opts


"""NTuple config for HLT TDR

You should try and put any centralised changes in generate_process(), not here.
"""


process = generate_process(year="HLTTDR", useData=False)

# Please do not commit changes to source filenames - used for consistency testing
process.source.fileNames = cms.untracked.vstring([
    '/store/mc/Phase2HLTTDRSummer20ReRECOMiniAOD/QCD_Pt_300to470_TuneCP5_14TeV_pythia8/GEN-SIM-DIGI-RAW-MINIAOD/NoPU_111X_mcRun4_realistic_T15_v1-v1/100000/16A7C8FA-DDE1-2945-A50C-C8F8A79749A7.root'
])

# Do this after setting process.source.fileNames, since we want the ability to override it on the commandline
options = setup_opts()
parse_apply_opts(process, options)

from HLTrigger.Configuration.common import producers_by_type
for producer in producers_by_type(process, 'PATJetProducer'):
  producer.discriminatorSources = []
  producer.tagInfoSources = []
for producer in producers_by_type(process, 'PATJetUpdater'):
  producer.discriminatorSources = []
  producer.tagInfoSources = []
for _tmp in process.MyNtuple.TopJets:
  del _tmp.higgstaginfo_source

with open('pydump_mc_HLTTDR.py', 'w') as f:
    f.write(process.dumpPython())
