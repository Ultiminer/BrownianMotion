import numpy as np
import matplotlib.pyplot as plt


arrayStats   = np.loadtxt('stats.txt', comments="//", delimiter=":", unpack=True)


[kStats,dStats]=np.polyfit(arrayStats[0,:],arrayStats[1,:],1)

minStats=np.min(arrayStats[0,:])
maxStats=np.max(arrayStats[0,:])


plt.plot(arrayStats[0,:],arrayStats[1,:],'ys',markersize=5)
plt.plot([minStats,maxStats],[dStats+minStats*kStats,dStats+maxStats*kStats],'y')
plt.legend([f'k={kStats}']);
plt.show()