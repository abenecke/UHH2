# This is a small example how the crab api can easily be used to create something like multi crab.
# It has some additional features like also creating the xml files for you. 
# For it to work you need inputDatasets & requestNames apart from the classical part 
#
# Make sure to have a unique directory where your joboutput is saved, otherwise the script gets confused and you too!!
#
# Usage ./CrabConfig ConfigFile [options]
#
# Take care here to make the request names *nice*
# 
# autocomplete_Datasets(ListOfDatasets) works also for several entries with *
#
from DasQuery import autocomplete_Datasets

#inputDatasets = ['/DYJetsToLL_M-50_HT-*to*_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_*/MINIAODSIM']
inputDatasets = ['/QCD_Pt-15to7000_TuneCUETP8M1_Flat_13TeV_pythia8/RunIIFall17MiniAODv2-FlatPU0to70_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM']
inputDatasets = autocomplete_Datasets(inputDatasets)
requestNames = []
for x in inputDatasets:
    name = x.split('/')[1]
    modified_name =name.replace('_TuneCUETP8M1_13TeV-madgraphMLM-pythia8','')
    if 'ext1' in x:
        modified_name += '_ext1'
    elif 'ext2' in x:
        modified_name += '_ext2'
    elif 'ext' in x:
        modified_name += '_ext'
    requestNames.append(modified_name)


# ===============================================================================
# Classical part of crab, after resolving the * it uses in the example below just the first entry
#

from CRABClient.UserUtilities import config, getUsernameFromSiteDB
from CRABClient.ClientExceptions import ProxyException
import os

config = config()
config.General.workArea = 'crab_PUPPI_QCD_2017_orig'
config.General.transferOutputs = True
config.General.transferLogs = True
        
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = os.path.join(os.environ['CMSSW_BASE'], 'src/UHH2/core/python/ntuplewriter_mc_2017v2_PUPPI.py')
config.JobType.outputFiles = ["Ntuple.root"]
config.JobType.maxMemoryMB = 3000
        
config.Data.inputDBS = 'global'
config.Data.splitting = 'EventAwareLumiBased'
config.Data.unitsPerJob = 7500
try:
    config.Data.outLFNDirBase = '/store/user/%s/RunII_102X_v1/PUPPIStudies/QCD_2017_orig/' % (getUsernameFromSiteDB())
except ProxyException as e:
    print "Encountered ProxyException:"
    print e.message
    print "Not setting config.Data.outLFNDirBase, will use default"

config.Data.publication = False
config.JobType.sendExternalFolder = True 
#config.Data.allowNonValidInputDataset = True
#config.Data.publishDataName = 'CRAB3_tutorial_May2015_MC_analysis'

config.Site.storageSite = 'T2_DE_DESY'

if len(inputDatasets) > 0 and len(requestNames) > 0:
    config.General.requestName = requestNames[0]
    config.Data.inputDataset = inputDatasets[0]


