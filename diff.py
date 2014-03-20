#!/usr/bin/python

import math
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
from matplotlib import rc

rc('text', usetex=True)

##################################################################
#x = np.arange(0,1,0.01)
#y = 0*x

# 20cm
data20cm = np.loadtxt('0613_20cm_diff')
(m20,n20) = data20cm.shape
x20 = (1.0/m20)*np.arange(0,m20)

#print m,n
#################################################################
plt.figure(figsize=(8,11), dpi=80)

#plt.ylim(-10.0,10.0)
#plt.plot(data1[:,2],data1[:,3],color='black',ls='-')
#plt.plot(data1[:,2],L,color='red',ls='-')
#plt.plot(data1[:,2],data1[:,4],color='blue',ls='-')
#plt.plot(data1[:,2],data1[:,5],color='blue',ls='-')
#plt.plot(phix,phiy,'b.')

#############################################################################################
gs2 = gridspec.GridSpec(n20, 1)
gs2.update(left=0.08, right=0.98, top=0.6, bottom=0.3, wspace=0.2, hspace=0.01)

ax20 = []
for i in np.arange(0,n20):
	ax20.append(plt.subplot(gs2[i, 0]))

for i in np.arange(0,n20):
	ax20[i].set_yticks([])
	ax20[i].set_yticklabels([])
	ax20[i].set_xlim(0,1)
	ax20[i].set_xticks([])
	ax20[i].set_xticklabels([])
	ax20[15].set_xticks(np.arange(0,1.1,0.1))
	ax20[15].set_xticklabels(np.arange(0,1.1,0.1))
	ax20[i].plot(x20,data20cm[:,i])

'''
#############################################################################################
gs3 = gridspec.GridSpec(n50, 1)
gs3.update(left=0.08, right=0.98, top=0.25, bottom=0.05, wspace=0.2, hspace=0.01)

ax50 = []
for i in np.arange(0,n50):
	ax50.append(plt.subplot(gs3[i, 0]))

for i in np.arange(0,n50):
	ax50[i].set_yticks([])
	ax50[i].set_yticklabels([])
	ax50[i].set_xlim(0,1)
	ax50[i].set_xticks([])
	ax50[i].set_xticklabels([])
	ax50[6].set_xticks(np.arange(0,1.1,0.1))
	ax50[6].set_xticklabels(np.arange(0,1.1,0.1))
	ax50[i].plot(x50,data50cm[:,i])

###########################################################################
#ax1.set_title('10cm')

#ax1.set_ylabel('PA (deg)',labelpad=0,fontsize=10)
#ax1.set_ylim(-120,120)
#ax1.set_yticks([-100,0,100])
ax1.set_xlim(0.2,0.8)
ax1.errorbar(phix10cm, phiy10cm, yerr=error10cm, fmt='.', markersize=2, capsize=0)
#ax1.plot(phix10cm,phiy10cm,'b.',markersize=2)
#ax1.plot(x,s,'r-')

#plt.subplot(222)
ax2.set_ylabel('Flux density (mJy)',labelpad=20,fontsize=10)
ax2.text(0.05, 0.85, '3100.0 MHz',horizontalalignment='left',verticalalignment='bottom',transform=ax2.transAxes,fontsize=10)
ax2.set_xlim(0.2,0.8)
ax2.set_xticklabels([])
#ax2.set_ylim(-0.8,8)
ax2.set_ylim(down10cm,up10cm)
ax2.set_yticks([0,2,4,6])
#ax2.set_yticklabels([0,200,400,600])
ax2.plot(phase10cm,prof10cm[:,0],color='black')
ax2.plot(phase10cm,prof10cm[:,3],color='red',linestyle=':')
ax2.plot(phase10cm,prof10cm[:,4],color='blue',linestyle='-.')
ax2.plot(x,y,color='black',linestyle='--')
#ax2.plot(x,s,'r-')

#ax3 = plt.subplot(223)
#ax3 = plt.subplot(223, sharex=ax1)
ax3.set_ylim(res_down10cm,res_up10cm)
#ax3.set_ylim(-0.8,0.8)
ax3.set_yticks([-0.6,0,0.6])
ax3.set_xticklabels([])
ax3.set_xlim(0.2,0.8)
ax3.plot(phase10cm,prof10cm[:,0],color='black')
ax3.plot(phase10cm,prof10cm[:,3],color='red',linestyle=':')
ax3.plot(phase10cm,prof10cm[:,4],color='blue',linestyle='-.')
ax3.plot(x,y,color='black',linestyle='--')
#ax3.plot(x,s,'r-')

#plt.subplot(224)
ax4.set_ylim(-120,120)
ax4.set_yticks([-100,0,100])
#ax4.set_ylim(-15,20)
#ax4.set_yticks([-15,0,15])
ax4.set_title('20cm')
ax4.set_xticklabels([])
ax4.set_xlim(0.2,0.8)
ax4.errorbar(phix20cm, phiy20cm, yerr=error20cm, fmt='.', markersize=2, capsize=0)
#ax4.plot(phix20cm,phiy20cm,'b.')
#ax4.plot(x,c,color='black',lw=5,ls='--')
#ax4.plot(x,s,'r-')

ax5.text(0.05, 0.85, '1369.0 MHz',horizontalalignment='left',verticalalignment='bottom',transform=ax5.transAxes,fontsize=10)
ax5.set_ylim(down20cm,up20cm)
ax5.set_yticks([0,5,10,15])
ax5.set_xticklabels([])
ax5.set_xlim(0.2,0.8)
ax5.plot(phase20cm,prof20cm[:,0],color='black')
ax5.plot(phase20cm,prof20cm[:,3],color='red',linestyle=':')
ax5.plot(phase20cm,prof20cm[:,4],color='blue',linestyle='-.')
ax5.plot(x,y,color='black',linestyle='--')
#ax5.plot(x,c,color='black',lw=5,ls='--')
#ax5.plot(x,s,'r-')

ax6.set_ylim(res_down20cm,res_up20cm)
ax6.set_yticks([-0.4,0,0.4])
ax6.set_xticklabels([])
ax6.set_xlim(0.2,0.8)
ax6.plot(phase20cm,prof20cm[:,0],color='black')
ax6.plot(phase20cm,prof20cm[:,3],color='red',linestyle=':')
ax6.plot(phase20cm,prof20cm[:,4],color='blue',ls='-.')
ax6.plot(x,y,color='black',linestyle='--')
#ax6.plot(x,c,color='black',lw=5,ls='--')
#ax6.plot(x,s,'r-')

ax7.set_ylim(-120,120)
ax7.set_yticks([-100,0,100])
ax7.set_title('50cm')
ax7.set_xticklabels([])
ax7.set_xlim(0.2,0.8)
ax7.errorbar(phix50cm, phiy50cm, yerr=error50cm, fmt='.', markersize=2, capsize=0)
#ax7.plot(phix50cm,phiy50cm,'b.')
#ax7.plot(x,c,color='black',lw=5,ls='--')

ax8.text(0.05, 0.85, '728.0 MHz',horizontalalignment='left',verticalalignment='bottom',transform=ax8.transAxes,fontsize=10)
ax8.set_ylim(down50cm,up50cm)
ax8.set_yticks([0,50,100])
ax8.set_xticklabels([])
ax8.set_xlim(0.2,0.8)
ax8.plot(phase50cm,prof50cm[:,0],color='black')
ax8.plot(phase50cm,prof50cm[:,3],color='red',ls=':')
ax8.plot(phase50cm,prof50cm[:,4],color='blue',ls='-.')
ax8.plot(x,y,color='black',ls='--')
#ax8.plot(x,c,color='black',lw=5,ls='--')

ax9.set_ylim(res_down50cm,res_up50cm)
ax9.set_yticks([-1.5,0,1.5])
ax9.set_xticklabels([])
ax9.set_xlim(0.2,0.8)
ax9.plot(phase50cm,prof50cm[:,0],color='black')
ax9.plot(phase50cm,prof50cm[:,3],color='red',ls=':')
ax9.plot(phase50cm,prof50cm[:,4],color='blue',ls='-.')
ax9.plot(x,y,color='black',ls='--')
#ax9.plot(x,c,color='black',lw=5,ls='--')

#############################################################################################
gs2 = gridspec.GridSpec(3, 3)
gs2.update(left=0.08, right=0.98, top=0.63, bottom=0.44, wspace=0.2, hspace=0.01)
ax10 = plt.subplot(gs2[0, 0])
ax11 = plt.subplot(gs2[1:3, 0])

ax12 = plt.subplot(gs2[0, 1])
ax13 = plt.subplot(gs2[1:3, 1])

ax14 = plt.subplot(gs2[0, 2])
ax15 = plt.subplot(gs2[1:3, 2])

ax10.set_ylim(-120,120)
ax10.set_yticks([-100,0,100])
ax10.set_ylabel('PA (deg)',labelpad=0,fontsize=10)
ax10.set_xticklabels([])
ax10.set_xlim(0.2,0.8)
ax10.errorbar(phix11, phiy11, yerr=error11, fmt='.', markersize=2, capsize=0)
#ax10.plot(phix11,phiy11,'b.')

ax11.text(0.05, 0.85, '3516.5 MHz',horizontalalignment='left',verticalalignment='bottom',transform=ax11.transAxes,fontsize=10)
#ax11.text(0.05, 0.85, 'Channel 1',horizontalalignment='left',verticalalignment='bottom',transform=ax11.transAxes,fontsize=10)
ax11.set_ylim(down10cm,up10cm)
ax11.set_yticks([0,2,4,6])
ax11.set_yticklabels([])
#ax11.set_ylabel('Flux density (mJy)',labelpad=9,fontsize=10)
ax11.set_xticklabels([])
ax11.set_xlim(0.2,0.8)
ax11.plot(phase11,prof11[:,0],color='black')
ax11.plot(phase11,prof11[:,3],color='red',ls=':')
ax11.plot(phase11,prof11[:,4],color='blue',ls='-.')
ax11.plot(x,y,color='black',ls='--')
#ax10.plot(x,c,color='black',lw=5,ls='--')

ax12.set_ylim(-120,120)
ax12.set_yticks([-100,0,100])
ax12.set_xticklabels([])
ax12.set_xlim(0.2,0.8)
ax12.errorbar(phix21, phiy21, yerr=error21, fmt='.', markersize=2, capsize=0)
#ax12.plot(phix21,phiy21,'b.')

ax13.text(0.05, 0.85, '1456.9 MHz',horizontalalignment='left',verticalalignment='bottom',transform=ax13.transAxes,fontsize=10)
#ax13.text(0.05, 0.85, 'Channel 1',horizontalalignment='left',verticalalignment='bottom',transform=ax13.transAxes,fontsize=10)
ax13.set_ylim(down20cm,up20cm)
ax13.set_yticks([0,5,10])
ax13.set_yticklabels([])
ax13.set_xticklabels([])
ax13.set_xlim(0.2,0.8)
ax13.plot(phase21,prof21[:,0],color='black')
ax13.plot(phase21,prof21[:,3],color='red',ls=':')
ax13.plot(phase21,prof21[:,4],color='blue',ls='-.')
ax13.plot(x,y,color='black',ls='--')
#ax10.plot(x,c,color='black',lw=5,ls='--')

ax14.set_ylim(-120,120)
ax14.set_yticks([-100,0,100])
ax14.set_xticklabels([])
ax14.set_xlim(0.2,0.8)
ax14.errorbar(phix31, phiy31, yerr=error31, fmt='.', markersize=2, capsize=0)
#ax14.plot(phix31,phiy31,'b.')

#ax15.text(0.05, 0.85, 'Channel 1',horizontalalignment='left',verticalalignment='bottom',transform=ax15.transAxes,fontsize=10)
ax15.text(0.05, 0.85, '749.9 MHz',horizontalalignment='left',verticalalignment='bottom',transform=ax15.transAxes,fontsize=10)
ax15.set_ylim(down50cm,up50cm)
ax15.set_yticks([0,50,100])
ax15.set_xticklabels([])
ax15.set_xlim(0.2,0.8)
ax15.plot(phase31,prof31[:,0],color='black')
ax15.plot(phase31,prof31[:,3],color='red',ls=':')
ax15.plot(phase31,prof31[:,4],color='blue',ls='-.')
ax15.plot(x,y,color='black',ls='--')
#ax10.plot(x,c,color='black',lw=5,ls='--')

#############################################################################################
gs3 = gridspec.GridSpec(3, 3)
gs3.update(left=0.08, right=0.98, top=0.43, bottom=0.24, wspace=0.2, hspace=0.01)
ax16 = plt.subplot(gs3[0, 0])
ax17 = plt.subplot(gs3[1:3, 0])

ax18 = plt.subplot(gs3[0, 1])
ax19 = plt.subplot(gs3[1:3, 1])

ax20 = plt.subplot(gs3[0, 2])
ax21 = plt.subplot(gs3[1:3, 2])

ax16.set_ylabel('PA (deg)',labelpad=0,fontsize=10)
ax16.set_ylim(-120,120)
ax16.set_yticks([-100,0,100])
ax16.set_xticklabels([])
ax16.set_xlim(0.2,0.8)
ax16.errorbar(phix12, phiy12, yerr=error12, fmt='.', markersize=2, capsize=0)
#ax16.plot(phix12,phiy12,'b.')

#ax17.set_ylabel('Flux density (mJy)',labelpad=9,fontsize=10)
#ax17.text(0.05, 0.85, 'Channel 7',horizontalalignment='left',verticalalignment='bottom',transform=ax17.transAxes,fontsize=10)
ax17.text(0.05, 0.85, '3132.5 MHz',horizontalalignment='left',verticalalignment='bottom',transform=ax17.transAxes,fontsize=10)
ax17.set_ylim(down10cm,up10cm)
ax17.set_yticks([0,2,4,6])
ax17.set_yticklabels([])
ax17.set_xticklabels([])
ax17.set_xlim(0.2,0.8)
ax17.plot(phase12,prof12[:,0],color='black')
ax17.plot(phase12,prof12[:,3],color='red',ls=':')
ax17.plot(phase12,prof12[:,4],color='blue',ls='-.')
ax17.plot(x,y,color='black',ls='--')
#ax10.plot(x,c,color='black',lw=5,ls='--')

ax18.set_ylim(-120,120)
ax18.set_yticks([-100,0,100])
ax18.set_xticklabels([])
ax18.set_xlim(0.2,0.8)
ax18.errorbar(phix22, phiy22, yerr=error22, fmt='.', markersize=2, capsize=0)
#ax18.plot(phix22,phiy22,'b.')

#ax19.text(0.05, 0.85, 'Channel 7',horizontalalignment='left',verticalalignment='bottom',transform=ax19.transAxes,fontsize=10)
ax19.text(0.05, 0.85, '1360.9 MHz',horizontalalignment='left',verticalalignment='bottom',transform=ax19.transAxes,fontsize=10)
ax19.set_ylim(down20cm,up20cm)
ax19.set_yticks([0,5,10])
ax19.set_yticklabels([])
ax19.set_xticklabels([])
ax19.set_xlim(0.2,0.8)
ax19.plot(phase22,prof22[:,0],color='black')
ax19.plot(phase22,prof22[:,3],color='red',ls=':')
ax19.plot(phase22,prof22[:,4],color='blue',ls='-.')
ax19.plot(x,y,color='black',ls='--')
#ax10.plot(x,c,color='black',lw=5,ls='--')

ax20.set_ylim(-120,120)
ax20.set_yticks([-100,0,100])
ax20.set_xticklabels([])
ax20.set_xlim(0.2,0.8)
ax20.errorbar(phix32, phiy32, yerr=error32, fmt='.', markersize=2, capsize=0)
#ax20.plot(phix32,phiy32,'b.')

#ax21.text(0.05, 0.85, 'Channel 7',horizontalalignment='left',verticalalignment='bottom',transform=ax21.transAxes,fontsize=10)
ax21.text(0.05, 0.85, '731.1 MHz',horizontalalignment='left',verticalalignment='bottom',transform=ax21.transAxes,fontsize=10)
ax21.set_ylim(down50cm,up50cm)
ax21.set_yticks([0,50,100])
ax21.set_xticklabels([])
ax21.set_xlim(0.2,0.8)
ax21.plot(phase32,prof32[:,0],color='black')
ax21.plot(phase32,prof32[:,3],color='red',ls=':')
ax21.plot(phase32,prof32[:,4],color='blue',ls='-.')
ax21.plot(x,y,color='black',ls='--')
#ax10.plot(x,c,color='black',lw=5,ls='--')

#############################################################################################
gs4 = gridspec.GridSpec(3, 3)
gs4.update(left=0.08, right=0.98, top=0.23, bottom=0.04, wspace=0.2, hspace=0.01)
ax22 = plt.subplot(gs4[0, 0])
ax23 = plt.subplot(gs4[1:3, 0])

ax24 = plt.subplot(gs4[0, 1])
ax25 = plt.subplot(gs4[1:3, 1])

ax26 = plt.subplot(gs4[0, 2])
ax27 = plt.subplot(gs4[1:3, 2])

ax22.set_ylabel('PA (deg)',labelpad=0,fontsize=10)
ax22.set_ylim(-120,120)
ax22.set_yticks([-100,0,100])
ax22.set_xticklabels([])
ax22.set_xlim(0.2,0.8)
ax22.errorbar(phix13, phiy13, yerr=error13, fmt='.', markersize=2, capsize=0)
#ax22.plot(phix13,phiy13,'b.')

#ax23.set_ylabel('Flux density (mJy)',labelpad=16,fontsize=10)
#ax23.text(0.05, 0.85, 'Channel 15',horizontalalignment='left',verticalalignment='bottom',transform=ax23.transAxes,fontsize=10)
ax23.text(0.05, 0.85, '2745.5 MHz',horizontalalignment='left',verticalalignment='bottom',transform=ax23.transAxes,fontsize=10)
ax23.set_ylim(down10cm,up10cm)
ax23.set_xlabel('Phase')
ax23.set_yticks([0,2,4,6])
ax23.set_yticklabels([])
#ax23.set_xticklabels([])
ax23.set_xlim(0.2,0.8)
#ax23.set_xticks([-0.2,-0.1,0,0.1,0.2])
ax23.plot(phase13,prof13[:,0],color='black')
ax23.plot(phase13,prof13[:,3],color='red',ls=':')
ax23.plot(phase13,prof13[:,4],color='blue',ls='-.')
ax23.plot(x,y,color='black',ls='--')
#ax23.plot(data13[:,2],data13[:,5],'b.')
#ax23.plot(data13[:,2],data13[:,5],color='red')
#ax10.plot(x,c,color='black',lw=5,ls='--')

ax24.set_ylim(-120,120)
ax24.set_yticks([-100,0,100])
ax24.set_xticklabels([])
ax24.set_xlim(0.2,0.8)
ax24.errorbar(phix23, phiy23, yerr=error23, fmt='.', markersize=2, capsize=0)
#ax24.plot(phix23,phiy23,'b.')

#ax25.text(0.05, 0.85, 'Channel 15',horizontalalignment='left',verticalalignment='bottom',transform=ax25.transAxes,fontsize=10)
ax25.text(0.05, 0.85, '1264.4 MHz',horizontalalignment='left',verticalalignment='bottom',transform=ax25.transAxes,fontsize=10)
ax25.set_xlabel('Phase')
ax25.set_ylim(down20cm,up20cm)
ax25.set_yticks([0,5,10])
ax25.set_yticklabels([])
#ax25.set_xticklabels([])
ax25.set_xlim(0.2,0.8)
#ax25.set_xticks([-0.2,-0.1,0,0.1,0.2])
ax25.plot(phase23,prof23[:,0],color='black')
ax25.plot(phase23,prof23[:,3],color='red',ls=':')
ax25.plot(phase23,prof23[:,4],color='blue',ls='-.')
ax25.plot(x,y,color='black',ls='--')
#ax10.plot(x,c,color='black',lw=5,ls='--')

ax26.set_ylim(-120,120)
ax26.set_yticks([-100,0,100])
ax26.set_xticklabels([])
ax26.set_xlim(0.2,0.8)
ax26.errorbar(phix33, phiy33, yerr=error33, fmt='.', markersize=2, capsize=0)
#ax26.plot(phix33,phiy33,'b.')

#ax27.text(0.05, 0.85, 'Channel 15',horizontalalignment='left',verticalalignment='bottom',transform=ax27.transAxes,fontsize=10)
ax27.text(0.05, 0.85, '718.2 MHz',horizontalalignment='left',verticalalignment='bottom',transform=ax27.transAxes,fontsize=10)
ax27.set_xlabel('Phase')
ax27.set_ylim(down50cm,up50cm)
ax27.set_yticks([0,50,100])
#ax27.set_xticklabels([])
ax27.set_xlim(0.2,0.8)
#ax27.set_xticks([-0.2,-0.1,0,0.1,0.2])
ax27.plot(phase33,prof33[:,0],color='black')
ax27.plot(phase33,prof33[:,3],color='red',ls=':')
ax27.plot(phase33,prof33[:,4],color='blue',ls='-.')
ax27.plot(x,y,color='black',ls='--')
#ax27.plot(data33[:,2],data33[:,4],color='black')
#ax27.plot(data33[:,2],data33[:,5],color='red')
#ax10.plot(x,c,color='black',lw=5,ls='--')

#############################################################################################

plt.savefig("test.ps",dpi=80)
'''

plt.show()



