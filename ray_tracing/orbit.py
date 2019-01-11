import math

duration = 1
interval = 1 / float(30)

sx = 250
sy = 250
sr = 40
se = 4.0

px = 350
py = 200
pr = 35
pe = 2.0
pomega = math.pi

mx = 290
my = 250
mr = 20
me = 0.5
momega = -3 * math.pi

spd = math.sqrt((px - sx)**2 + (py - sy)**2)
pmd = math.sqrt((px - mx)**2 + (py - my)**2)

t = 0
while t < duration:
    ptheta = t * pomega
    mtheta = t * momega
    
    px = sx + spd * math.cos(ptheta)
    py = sy + spd * math.sin(ptheta)

    mx = px + pmd * math.cos(mtheta)
    my = py + pmd * math.sin(mtheta)

    print("%f %f %f %f %f %f %f %f %f %f %f %f" % (sx, sy, sr, se, px, py, pr, pe, mx, my, mr, me))
    
    t = t + interval
    
