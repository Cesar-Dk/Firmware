   q31_t postShift;                               /* Post shift to be applied to weight after reciprocal calculation */
        q31_t coef;                                    /* Temporary variable for coef */
        q31_t acc_l, acc_h;                            /* Temporary input */
        uint32_t uShift = ((uint32_t) S->postShift + 1U);
        uint32_t lShift = 32U - uShift;                /*  Shift to be applied to the output */

  energy = S->energy;
  x0 = S->x0;

  /* S->pState points to buffer which contains previous frame (numTaps - 1) samples */
  /* pStateCurnt points to the location where the new input data should be written */
  pStateCurnt = &(S->pState[(numTaps - 1U)]);

  /* initialise loop count */
  blkCnt = blockSize;

  while (blkCnt > 0U)
  {
    /* Copy the new input sample into the state buffer */
    *pStateCurnt++ = *pSrc;

    /* Initialize pState pointer */
    px = pState;

    /* Initialize coefficient pointer */
    pb = pCoeffs;

    /* Read the sample from input buffer */
    in = *pSrc++;

    /* Update the energy calculation */
    energy = (q31_t) ((((q63_t) energy << 32) - (((q63_t) x0 * x0) << 1)) >> 32);
    energy = (q31_t) (((((q63_t) in * in) << 1) + (energy << 32)) >> 32);

    /* Set the accumulator to zero */
    acc = 0;

#if defined (ARM_MATH_LOOPUNROLL)

    /* Loop unrolling: Compute 4 taps at a time. */
    tapCnt = numTaps >> 2U;

    while (tapCnt > 0U)
    {
      /* Perform the multiply-accumulate */
      /* acc +=  b[N] * x[n-N] */
      acc += ((q63_t) (*px++)) * (*pb++);

      /* acc +=  b[N-1] * x[n-N-1] */
      acc += ((q63_t) (*px++)) * (*pb++);

      /* acc +=  b[N-2] * x[n-N-2] */
      acc += ((q63_t) (*px++)) * (*pb++);

      /* acc +=  b[N-3] * x[n-N-3] */
      acc += ((q63_t) (*px++)) * (*pb++);

      /* Decrement loop counter */
      tapCnt--;
    }

    /* Loop unrolling: Compute remaining taps */
    tapCnt = numTaps % 0x4U;

#else

    /* Initialize tapCnt with number of samples */
    tapCnt = numTaps;

#endif /* #if defined (ARM_MATH_LOOPUNROLL) */

    while (tapCnt > 0U)
    {
      /* Perform the multiply-accumulate */
      acc += ((q63_t) (*px++)) * (*pb++);

      /* Decrement the loop counter */
      tapCnt--;
    }

    /* Converting the result to 1.31 format */
    /* Calc lower part of acc */
    acc_l = acc & 0xffffffff;

    /* Calc upper part of acc */
    acc_h = (acc >> 32) & 0xffffffff;

    acc = (uint32_t) acc_l >> lShift | acc_h << uShift;

    /* Store the result from accumulator into the destination buffer. */
    *pOut++ = (q31_t) acc;

    /* Compute and store error */
    e = *pRef++ - (q31_t) acc;
    *pErr++ = e;

    /* Calculates the reciprocal of energy */
    postShift = arm_recip_q31(energy + DELTA_Q31, &oneByEnergy, &S->recipTable[0]);

    /* Calculation of product of (e * mu) */
    errorXmu = (q31_t) (((q63_t) e * mu) >> 31);

    /* Weighting factor for the normalized version */
    w = clip_q63_to_q31(((q63_t) errorXmu * oneByEnergy) >> (31 - postShift));

    /* Initialize pState pointer */
    px = pState;

    /* Initialize coefficient pointer */
    pb = pCoeffs;

#if defined (ARM_MATH_LOOPUNROLL)

    /* Loop unrolling: Compute 4 taps at a time. */
    tapCnt = numTaps >> 2U;

    /* Update filter coefficients */
    while (tapCnt > 0U)
    {
      /* Perform the multiply-accumulate */

      /* coef is in 2.30 format */
      coef = (q31_t) (((q63_t) w * (*px++)) >> (32));
      /* get coef in 1.31 format by left shifting */
      *pb = clip_q63_to_q31((q63_t) * pb + (coef << 1U));
      /* update coefficient buffer to next coefficient */
      pb++;

      coef = (q31_t) (((q63_t) w * (*px++)) >> (32));
      *pb = clip_q63_to_q31((q63_t) * pb + (coef << 1U));
      pb++;

      coef = (q31_t) (((q63_t) w * (*px++)) >> (32));
      *pb = clip_q63_to_q31((q63_t) * pb + (coef << 1U));
      pb++;

      coef = (q31_t) (((q63_t) w * (*px++)) >> (32));
      *pb = clip_q63_to_q31((q63_t) * pb + (coef << 1U));
      pb++;

      /* Decrement loop counter */
      tapCnt--;
    }

    /* Loop unrolling: Compute remaining taps */
    tapCnt = numTaps % 0x4U;

#else

    /* Initialize tapCnt with number of samples */
    tapCnt = numTaps;

#endif /* #if defined (ARM_MATH_LOOPUNROLL) */

    while (tapCnt > 0U)
    {
      /* Perform the multiply-accumulate */
      coef = (q31_t) (((q63_t) w * (*px++)) >> (32));
      *pb = clip_q63_to_q31((q63_t) * pb + (coef << 1U));
      pb++;

      /* Decrement loop counter */
      tapCnt--;
    }

    /* Read the sample from state buffer */
    x0 = *pState;

    /* Advance state pointer by 1 for the next sample */
    pState = pState + 1;

    /* Decrement loop counter */
    blkCnt--;
  }

  /* Save energy and x0 values for the next frame */
  S->energy = (q31_t) energy;
  S->x0 = x0;

  /* Processing is complete.
     Now copy the last numTaps - 1 samples to the start of the state buffer.
     This prepares the state buffer for the next function call. */

  /* Points to the start of the pState buffer */
  pStateCurnt = S->pState;

  /* copy data */
#if defined (ARM_MATH_LOOPUNROLL)

  /* Loop unrolling: Compute 4 taps at a time. */
  tapCnt = (numTaps - 1U) >> 2U;

  while (tapCnt > 0U)
  {
    *pStateCurnt++ = *pState++;
    *pStateCurnt++ = *pState++;
    *pStateCurnt++ = *pState++;
    *pStateCurnt++ = *pState++;

    /* Decrement loop counter */
    tapCnt--;
  }

  /* Loop unrolling: Compute remaining taps */
  tapCnt = (numTaps - 1U) % 0x4U;

#else

  /* Initialize tapCnt with number of samples */
  tapCnt = (numTaps - 1U);

#endif /* #if defined (ARM_MATH_LOOPUNROLL) */

  while (tapCnt > 0U)
  {
    *pStateCurnt++ = *pState++;

    /* Decrement loop counter */
    tapCnt--;
  }

}

/**
  @} end of LMS_NORM group
 */
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            ���� JFIF      �� Compressed by jpeg-recompress�� � 	
	
	!!1&""&18/-/8D==DVQVpp�	
	
	!!1&""&18/-/8D==DVQVpp��� 	" �� 5                           ��     �1X8�Z��G!�u���A&���L�Q    L� @@�B%�A�0B	H�5%l�X�z�\Mn�@�˟�7c��5o�E��Y{W������XA�� �������d�Cf������5,>wg��Nq.��T,����e����˯oe_ 鼏}dq�^Ԅ�D�q�D��A G(��JI���2?"�K���t٭�(�� 70��Z�HTE���:�g��gs.���\����|� |� �`�d�|0e|�����a܇C���ɪ����Ȧ=�ĳ�'c���*uvVӆ$0%YJg����������  �� @d	�����x
���~�/��e{E7���m�����S�c�Oo��WcO��sᙷe/)��8�B������*n<���BB�	 `R	{=}��x�q�f�^*W|��|˫���K�nz�AC��^E���z�T� �����e{K��aYZ�鞗~��s�  �BT@JHD ����]��P��v�]k��0��.�ed�	K�_>�ܾ��u:��Q��V�����u/A�����X�jk�T���7� � @ D � 3H�����'���#z�<`yg[��~%�A��vp:Ed*�'2V��ׯF|��ڷc=��[��K�ӻVY2�7�f [�T�  H     #��qw�澫�ݿO�����Wo1�����f�W��SZ�h!5��&3UGkWR��� I� 2   �*D\��Bn'h园F�CBRf/�E��h|���Rs�V&�ӛj���Z�ژ��ϩ����,;k��'�Q�.x���#��pXDY�o�5�fĪ��l���q���Q���'����M�u���z��Fb�yS4�:>:�*���R�g`�x�g�\�!{�A�U�L��A���
��&Σa.2�TsYvT'��������k���ֿ^�-e���H��ʪ+Y��-���钏^S�^�a�sJ����= ��Iq�GA�l�'�sе"�ͧ(�4�_h���Ф��z�7\6�6m��zT�l�2is}����=�Ov[$@��� a�F2g�NuA^�w���gd�[
)lƥ���� �[��ڼ��h���`�����l�.	VU&�&��G���i�+b������z�7Yb_���&��jg\Ш<���t9y�NEz�v4ɪ�ݠё�]��Iҽ����hy����õ9ú�lJi6s�wC��XVR���ǡ�ȳ���oҹ.�ר�洴�*�d��o�7�]��kX�����"���Iv�8������D;�uX�ݻY�Ufµ��m�L��7H��w�m�����+��2;�ckɖ��-���Vt�Ul�����;kk's�j��D��ưҲ�n�z\$�{Po%�<��r���NKCU�p���G���ʱ�*���G�� $         0��   u�٩�Z���������{߄_�������W�^v�������Z��峊�{�ܿM����������#�O>yd%J��D�y]n��{��w��{����{�B+
夯�5�[�b�/v+�-A��}�{Wo����m�{���<o���/d�����s\�@�{ߥ��ݻ��߷~��v�ߺ��7�Y|�#��=]�^���̅0�%�/�u~ݕݻw��_�d*G�H��X��D�h��_��X�LXd:�)�v�۶��_߿f)K�������@����G�G�ӏ���)�;�ֻv�+R��)oI�_F
��%č�d	"F#�X��Z�͌��e���^c�A�@b�(GVZ׽�b�^��$sוo�� �r���K��`D	�N��vY��TI�Q��wj�j9u�iSƼ��!RH_�:&��#�����N"�䏊�F��O�s_H�YI�IaL2p��aQ�j�h΢6���*1`�h���E�d���(-�qq�z>w�tvjFbE�����j1Q|o��~��R&�\"+�k��r�x�ؕ9�?�*�	�d��-J5<iU|��'X�31����96��.����	��0�
�j����������e%��"W�O��4�TAV-S+��0�$Q����eU�"L$��c좨���#o�)�Gb�B��;���}kU��䦙8[Ʉ�F1��X���Oژ�t!$�W!�<�M��MͮG[��⚄,�3���� �e���)KS}���F$q�t��Fx��#,fF5�e8�Y�䶹[u�u�٭��=�qm��ι[��[��᭖B$���r2�a���uhɮ�.�'#*U^"tHd�_��D�i�F�H*����#Y�l����I���J{<n0�'*U+�iX����$�UTz�@+;+���!I:rT�+�,�]?!�8i��+��� mzW�J�zLz�t��ª=^��ܒ�e��ř�D`�,�3��6Q%�sFHR%c��o�Q���Gv�WD�|6�%$X�KG�I2r�w�MN�Mnܑre�ߔI��L�r_�^*U,�EV��y^�r�b�V���/�� U��V������z�*���hx4���k(��k���hm.&)Nz�Q�kk�������J�rV%Sj�U��-0�Dإ���I??���L���L��o[�`!�WVՆ���"�ثKVKXj�$hΈ��i.>�#���K��H�pi�;�(zu�����]�ȍb"9A�p*���W�(3 �䨞�8�%!�Y)e�H�ad��GUϳ�(�v�������c%�C�☖�'fC���Wh9o�H�GhP�{��yA�+�ܡ��)���eѬ���T]�U[�N�'kF�@��,�#\C��[`��s�,�UZ�6(��4��Y�%T��*(��h����,�ᵟ�w̝��j���T�j�*N��S��8!�#Q�,9?1dN?������8�;��w��^'"��\o��� A    !1AQ"aqBR�02�� #�$3@br�%St��&c������  ? �=j��U9��N~3R���F�����G�nk��� ���Gl2���f�d$�s���X�p_��%����p���0�`��մ
$�r�^���0_�'�P�uG�����#��Y�>#ʞ�-dn�T�O@\��-q��r������n��ϙ���iX�`�t�P��)��I�EBĻ���(ڼ5٤F����0�QL��$b���s���tR
�ş��y�4���>��KbؚuL7Ïl�$U�,����/1ӐwƤ��\.P^+����w���
�~#��<��W\�d����%/�ճ��*�D�0�����s���� �SI߹Lg�AN�ca�0Uj��$�T��&�m(Pv�I ��*�6v<CB��`s�1NȾ9F��]��~J�e��)�(� �4h�p�2�����Y��H	ը��A�q�WX�b�I{juV�+���9�U'8#j���g~B�T����(�"��v�s��+Ed�4�<��m����AJ�u�{r�jK�b  �����k�H����o#Ԓ�o���`Сʿu��H팥<����\nx╭��1�_"�:|9���¾�:R%?:�&}�9�*i�H�������K1���38��(�,
���ݘ�L�Лw<�|O��� �;�}�TQ�6��*2�� :TD�����Z�G'��mMqiHٓH��?a�3��𱢱���cm�]G>%�4� ��7�'5}�$a,�*�ϟO~�R��K�����S�F;����%�ru6�
�0Ǎ� �@<݇z�&:���(7�SM�(��	�P�V��q�vn��d���Y�<dd��\p�&���� ��Rʊ�ɀ#��?�~�p0sR�+*)]�>t�w�ď(�S��W剤��l,� �(�;vڦNg�^i$:��l{�B�	b�p_�aLē��$l����)Q�t�O,��M�g�ڜs&��Ցȟ���5�E�����4H��/�07��.p$o,�H1$'C����C�� uսI�α��*��@?Ҽ&�ǕS��P���JKg\���� yG3F��$F,�D6<�1,�� �i���}*@p>�4� J�|y1���s�T�.� 㘢���cj��)��E����\��K!�0��1{V�)�/0}��`P����~���@��A�cH��Q��	�#s��yTVx&W�#B@�̌��К����\#�����Fu�%A鎦���3H (`�Tr#PE5��/N���4G1�Zn�R��A�wMj٧C�	,��`��`pQ�hI?u����vX.��حF	�g�}.	�OZ���:��94.��@X�X�n��ẕm��q�U����"�2p~�2ƈ�+���i'W{���cة���s"�7�J�)�}E8`3�u�RW�����\i�e�7�G�>�iW8�߱Q�Β��������ziӎ�w4�S\ƾh��RhO�9a����jp=|�4��)$�ڒ4wϵl2(��Y�#j��	>]�I��F<�zS��!�#p9W�?�n;�:��T���c��~��1S�U�����ۊ\HR>Q�R�"�W�i��� `G֋:���^�3��#��b�H�;s�t����z��#Њ�(��ԋ�ӡ$��aD�f:� ��B�X�s��PĀcJ��}���0�(�S���_�"]��G2��F����E=t���
���Jr�@�h�����%b�\՜�xs)�ұ�3H���� 1�V0�P�����c���8�O�NI��M$�)Ḛ,~5��� ´��Y��k*���K��u9؊��x��Q�2�4.q� 3�P��Eܗ���p[A�MY�k6�w�¦�\v���5���y0v�&�g�5y#X
-
�8�d%MO}p�����j��x��<�2k��o�� ��\> \p� '��	r�[d�?�Cf����1�� ~<Wm3��.`�#ڼ���H/�˜ �s�[r�c�E-���9K�q�d}��^'c ��O�Zk.j�0Dc4ng�җ�rU;-	&�mkm��@(��󊴴��[��v�@�W��ú�P��,�U���A>�H�q�I�W"���D���{&k����2r3Ǯ�R~����|�<��d�b�>f�@=���p������cW��+�#���tc������9SI[��O�g~��\ޟ����Iv�5g���Y[���g��d� � s+������I@��y0�ʣ��|>3�{�c7P9�"�U�{��yA/�yݎG���,��0�6�Q�ίn`�2L1K����>�K�V�(� �*�H�μg�Z�'���oWį���۴�!@rSB���[�Pi �b����	+v/@��¦'(J�_�S��e,Jƹ``
���Qw�Y�n��
D��6�~�IA�}k�l/�$Re�*G��������x���l�;f��|1$;�� �h5�E�nGjԤ�{Qy	/�TH�|��u
H��ǔ�\���Ҋ<��{�f��8��QQ��"��=�X�r���ރC2�CRZ��ϕ����k���}_���x�;�G��Fߑ�kȸ�L��X$w&�8��0\)�a�S�Z�����y�{Qs�`u�Eg4�1^o��
]��H��jF}��4 ̭�9� � V��
	�<�	�2Y�tάwcX�a�|����>� �x�8�t1�؞U%����I�. �?�п���Fe�A:��p��BXbpr���+T�m��h�+�����S�EWrX<��uh:3�5}BA��#��ՀE`#yO��e�.D��qg+��z1(l�$P���;���9;���&�D
e�9��f�p[ur7� -/zN���1֣�Q���j/���z�����3�L~h�SW|3����L��q�Z��Q#�TcҘ7�|�X�����y�ҵHkZ:�#Z�8=p�|]�>��'5m�P�B���!a�-ԚuӭG]��X���ʡA#q��py�w�d6�A��8	���ì��B�5�+����B�u\�|�!�R�/�R�����C�S��z��(�w�޽h������n?������Ζ�d6�Ddd��F��<-,f:�8SD�m[�s������Av؝�*���9�ˑ� pj���1b�Ԏ����隉e�����cc�R�/�����*��o-6a��>��H@8m\�Ej��w9��W��٤�#ƂW��޴��J~R��MLG੏J���7cR���i�ΚW
(ʣ"��$�X�t`�Gu�;�ar�LTf<~�My{peb|C���@��QƗ
J���_>�I�RI+Hw�5uq1�;\c�m����T����ŁȆ��\Rlx�~�&�Y|k���hN�9��:^�`�aB(���0�?�5x�Gk�N3�^ԝ�>ZLr��Tcਇ�*!�TG���R��5�֑#P�X?f� ��F}*�8����:p}�F}�y�_*Tny��i�z�w���B�-�B*�!��z⬡o5�?�p퀑����鶃�֤,��t�����ɠѮ��ɡ��'��ֿ��=�)�]�ۥ1�M�W�`r��Ti�ʛ���լⴅ$V f?��#�6��].<���E4Y��`�|s��1H��H:�ѫE֯���� C˽�F	=>�p�9n*���˟�Co�W\��J�o�I^� ҉�s���Y�8�CH�3.�����b�t���������������28��q�f��� FĊ|�&��`J�'ҮxT����*>�H
*O�L����������#���Kim���$aؕ*y��c�;zT	�o�J5x@mL�2k�[�ɡq¸���r���5`ѷ�-ʆ���'�K��?���i�cR|���k V�>�}��ԞUøz�b��w�J�d���[��H�`� �D���V� U*ug�ɨ]�O	�N1�^l��?��FRьg.�9<�f�dT2�urrGe8�{u�=Yu�����SM��ȥ*}�X���m�5���{�@ׇ���� e��N;�����Y�&<�O*㳀�͠BG�r"�6	���n!�c@���d�ӊ��;e�vӘ��Z\��brF[��Y�Q�/:���>Z���J��57j�P($Cj���0�P[�(�A���W+4FbLR��>1�� m`���u���[I�ep9�5���R;�א(�s��	�d}$�Ρ�yj��(1� 	'��Z{[��eʔd��C���Mt1�l���ys��A�)�Zj"��O;��5��f�8�8���r�4��Ÿ�[Ț}3K?N!�$+� ��.�\����h�s�@9��Em�+���+o��
��ȟs���l �ֽ+~T��'jNսkp�R$`R�W$��-̦�و���|L:{
 9G3H Vذ`�=ڛ�����+�4ᶤ��<��=�{�� �xQ��)n���7Z>:J���Ú�S��HP7�1��f�G���.䜞�rj�Ё�֥�H��ڮ�lJ.��~���66�(F��A�P��!I
7��9џ��a¢��e����r�7j����˫��D���A-�xM���sܮ��SG�ӷZIX#�N�;P�J(P�L �I�K��
=m�C�wz�m�r��ќ,�"��[�_Ş��g�n#�' \�Yw��w�C�\%Ę�o��|���!��(N���ԅـ>c�H��R S�ˎE��Q��lc4f8|�'I���ib!H�F4d1���XǌЌ�� B6;c�������չ=([��8#�����]>�ly��Eq@ ������hq(,sl����c�'50Mk����Ѧ�<�j)�L��J�;�W	�0��D�i�s��4F� ���oJT);�FC��I�Y$�CF��f���k'��uj�juV��#�@oI��4� ֖'* �1Q#l7����g� ڴ�i��P�	^W��;����r_P�;�w$�ɬS���`!w#5u �诫mKgd��&�g?Z�ӄ��C��듵�$�Q�(m����֔RP�" ���wKtJ�v'
�Ԛ�wVV�\��ģ'��c\g�9Mr^Zt}:�s�(*�
��F�d�|�=*���pr@��.�Xw��F:SẊ>RwS�q��+*�TH;�I5�VI�a�.)S�m��c�Y�+Ĳ	%
��W|Vfw$�O���wl�a�jy\|��j�+;[�C�J� �ZNyndzT��͟�\W�o˭~ hY9o�����|�0��T8�
����#�_�����(4ئ�N��,�$?�n�/$PRbW*900��ْ�"��f:��aP�ܷ:T��&�C�e��t6����.X�+�����{�̣PF*ξ�ӌ�kd|8�gm�<+��6���z�)�⑒�hlsQp��cFQ#FX��A'�m�����J\#/r7�%Q���qPH2�!�5�d��I�Z�#/Q�������������b�ݤn�p+�^�S6�?l)�9jp�O3ʝ����C^�R�scʽ�D�;����H�<��h�t��54��d�ܧ�����I�\Z���s�m� =kB
���3,��>g��^�WQ��T%�䭌w�\:���}�S����� H�>�~v�V��HFڂ�/<JK���
/y�3�ddJA��v�+�5���2K�9�9���2����N�ir6�^��y?��� �� �N��s��X�<������ޘ֣�h�FsH�3�)�'V�i����I:J�AL��hZ�yQC� �zW���0{5��7�L_��>o��ٽ��� O-e� ���3{��oֶ�ה��Q[
�Vձ�f� �y���+��s� �}����W���=l+��� ,       !1AQ a"20Bbr��� ? �7�[�f�i��� z�ًǔ��x�,��:l����2xsƭlqkLK�1��1x불�!/DQ�<��<�X����,��,�\��1�E	И�e�2�T��<�O�t�-��f���Z]�qJ�y�MOhK֏3ɉ�u�{�/�B3ϊ��,Ǖ��e�֙~�5jI�\g5� /�Ğ�bg��,�lNI�Y'�9!Qn̏�����5}��令�b��}k�Q]2{#5k�O�1����-��$����f��q��d$�ޅ,U��Ԗ�َI=�7h�W?ajQfo#&9��&�ɿ������fI�Pl�4�r����;��1m�5���߹�x��z7���!�vd�=hJQ�1��d�K-�?a����|��� ��G�^�,i��Ľ���!A�MV�Vc�og�z-����%S�!t�񂤎L��l��F�Lx���0v7%*dT\{e)W��RDaJƶQL���"�BM��fv��
K�$���3鐅��No � [W�KѦ�d�*G'Cl���ƾ�[H�s��y"��7-#�w'�󎤨��MvN<Y���lJV[�#��U�r슔���}F�g1�%)T{e�,x嶣�Qk%�e��\vr��;g�%�'	Sw��&�kL��������Mw$�CIu	3���K���ŋ�U�r�eȂ}��-��G�̑R����))"qO�{��1M�(�b��<p���H�'���t);2/�vA*�� 1        !1A "Q2a#Rq�03BSb�� ? Hѵ"1�F��]#�P�m������±�@�N�4J�񘠶�����'������H6� ��D�đ�|K�!��8����[]��j�:���8Į�2AG�>G�s���Օ���#ã���{.���F����j���WIT�QiS�!c�v\CX�Q�7��}{�湮��#]��w���T*
��ڒ�`D�I�p�n%y)�s���æ���}�����ĵ��p�`q����=�u$/aTy���x�:֖O;O����~$��J;�OK� ��#*H�Გ.��vQ��F4wr���顎�h�qm1���)���V� 	^ozFW���\��xpn뼾����g�eiEj`�~ Q�X����k���b��{<�~��]8�(�/VvL#I���ț��pZ-,r��2�ј�c	�o��i!2O1�tHg*�ܧ�J�Z"��+����G�P�aaq��65�Ԋ���!CU'd�Ӧ��㼔KH���.��C!|�v�;��D|S`��vb�j?�N�>���|K���E�=ԜkW3K�\�F^�(���G�ܡ��Z�,a�)��B{�S��'�~D�O �Jd�-^ci1⺆
~�k��زr��J��� �)Q@F� ez�h쬌�H�F@{���@
x���IE�*?*�ʡ��5� @`��,$'F�v]��TQ�X���� �y��eȔ>�V�/�PSX X(�宐��I%:���XN5����B! ��b���<��DN� *(Hӳ�P����I������$�v�	�*�啑��Jk�R�sA
�;�w�*ͨś(�0����                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               /* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_fir_q31.c
 * Description:  Q31 FIR filter processing function
 *
 * $Date:        18. March 2019
 * $Revision:    V1.6.0
 *
 * Target Processor: Cortex-M cores
 * -------------------------------------------------------------------- */
/*
 * Copyright (C) 2010-2019 ARM Limited or its affiliates. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "arm_math.h"

/**
  @ingroup groupFilters
 */

/**
  @addtogroup FIR
  @{
 */

/**
  @brief         Processing function for Q31 FIR filter.
  @param[in]     S          points to an instance of the Q31 FIR filter structure
  @param[in]     pSrc       points to the block of input data
  @param[out]    pDst       points to the block of output data
  @param[in]     blockSize  number of samples to process
  @return        none

  @par           Scaling and Overflow Behavior
                   The function is implemented using an internal 64-bit accumulator.
                   The accumulator has a 2.62 format and maintains full precision of the intermediate multiplication results but provides only a single guard bit.
                   Thus, if the accumulator result overflows it wraps around rather than clip.
                   In order to avoid overflows completely the input signal must be scaled down by log2(numTaps) bits.
                   After all multiply-accumulates are performed, the 2.62 accumulator is right shifted by 31 bits and saturated to 1.31 format to yield the final result.

 @remark
                   Refer to \ref arm_fir_fast_q31() for a faster but less precise implementation of this filter.
 */

void arm_fir_q31(
  const arm_fir_instance_q31 * S,
  const q31_t * pSrc,
        q31_t * pDst,
        uint32_t blockSize)
{
        q31_t *pState = S->pState;                     /* State pointer */
  const q31_t *pCoeffs = S->pCoeffs;                   /* Coefficient pointer */
        q31_t *pStateCurnt;                            /* Points to the current sample of the state */
        q31_t *px;                                     /* Temporary pointer for state buffer */
  const q31_t *pb;                                     /* Temporary pointer for coefficient buffer */
        q63_t acc0;                                    /* Accumulator */
        uint32_t numTaps = S->numTaps;                 /* Number of filter coefficients in the filter */
        uint32_t i, tapCnt, blkCnt;                    /* Loop counters */

#if defined (ARM_MATH_LOOPUNROLL)
        q63_t acc1, acc2;                              /* Accumulators */
        q31_t x0, x1, x2;                              /* Temporary variables to hold state values */
        q31_t c0;                                      /* Temporary variable to hold coefficient value */
#endif

  /* S->pState points to state array which contains previous frame (numTaps - 1) samples */
  /* pStateCurnt points to the location where the new input data should be written */
  pStateCurnt = &(S->pState[(numTaps - 1U)]);

#if defined (ARM_MATH_LOOPUNROLL)

  /* Loop unrolling: Compute 4 output values simultaneously.
   * The variables acc0 ... acc3 hold output values that are being computed:
   *
   *    acc0 =  b[numTaps-1] * x[n-numTaps-1] + b[numTaps-2] * x[n-numTaps-2] + b[numTaps-3] * x[n-numTaps-3] +...+ b[0] * x[0]
   *    acc1 =  b[numTaps-1] * x[n-numTaps]   + b[numTaps-2] * x[n-numTaps-1] + b[numTaps-3] * x[n-numTaps-2] +...+ b[0] * x[1]
   *    acc2 =  b[numTaps-1] * x[n-numTaps+1] + b[numTaps-2] * x[n-numTaps]   + b[numTaps-3] * x[n-numTaps-1] +...+ b[0] * x[2]
   *    acc3 =  b[numTaps-1] * x[n-numTaps+2] + b[numTaps-2] * x[n-numTaps+1] + b[numTaps-3] * x[n-numTaps]   +...+ b[0] * x[3]
   */

  blkCnt = blockSize / 3;

 